/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:05:19 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/22 13:13:03 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_comand_in_pipe(t_sh *sh, int i, int in_fd, int pipefd[2])
{
	dup2(in_fd, STDIN_FILENO);
	if (i < sh->vars.cmds_num - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	close(in_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	if (check_if_builtin(sh->comands[i].cmd))
	{
		exec_builtin(sh, i);
		exit(g_status);
	}
	else if (execve(sh->comands[i].cmd, sh->comands[i].arg, sh->envp) == -1)
	{
		perror("Error executing command");
		exit(errno);
	}
}

static void	pipeline_exit(t_sh *sh, int in_fd, int i, pid_t *pids)
{
	i = 0;
	while (i < sh->vars.cmds_num)
	{
		after_execution(sh, pids[i]);
		i++;
	}
	free(pids);
	close(in_fd);
	i = 0;
	while (i < sh->vars.cmds_num)
	{
		wait(NULL);
		i++;
	}
}

void	execute_pipeline(t_sh *sh, int i)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	*pids;

	in_fd = STDIN_FILENO;
	pids = malloc(sizeof(pid_t) * (sh->vars.cmds_num + 1));
	prep_cmds_pipes(sh);
	if (filter_cmd_error(sh) == true)
		return ;
	while (i < sh->vars.cmds_num)
	{
		handle_redirects(sh, i);
		pipe(pipefd);
		pids[i] = fork();
		if (pids[i] == -1)
			get_out_of_pipe();
		if (pids[i] == 0)
			execute_comand_in_pipe(sh, i, in_fd, pipefd);
		close(pipefd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = pipefd[STDIN_FILENO];
		i++;
	}
	pipeline_exit(sh, in_fd, i, pids);
}

void	check_pipes(t_sh *sh)
{
	int	i;

	sh->vars.pipe_num = 0;
	sh->vars.is_pipe = false;
	i = 0;
	while (i < sh->vars.tk_num - 1)
	{
		if (ft_strncmp(sh->tokens[i].tokens, "|", 1) == 0)
		{
			sh->vars.pipe_num++;
			sh->vars.is_pipe = true;
		}
		i++;
	}
	i = 0;
	if (sh->vars.is_pipe)
		execute_pipeline(sh, i);
}
