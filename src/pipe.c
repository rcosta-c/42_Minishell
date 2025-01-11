/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:05:19 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/11 18:13:52 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_comand_in_pipe(t_sh *sh, int i, int in_fd, int pipefd[2])
{
	if (!sh->comands[i].cmd)
	{
		fprintf(stderr, "Command not found\n");
		exit(127);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
		handle_error_pipe("dup2 error on stdin", errno);
	if (i < sh->vars.cmds_num - 1)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			handle_error_pipe("dup2 error on stdout", errno);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (check_if_builtin(sh->comands[i].cmd))
	{
		exec_builtin(sh, i);
		exit(g_status);
	}
	if (execve(sh->comands[i].cmd, sh->comands[i].arg, sh->envp) == -1)
		handle_error_pipe("Error executing command", errno);
}

static void	finish_pipeline(t_sh *sh, pid_t *pids, int in_fd)
{
	int	i;

	i = 0;
	while (i < sh->vars.pipe_num)
	{
		wait_for_child(pids[i]);
		i++;
	}
	if (in_fd != 0)
		close(in_fd);
}

void	pipeline_helper(t_sh *sh, int i, pid_t *pids, int in_fd)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		handle_error_pipe("pipe creation failed", errno);
	pids[i] = fork();
	if (pids[i] == -1)
		handle_error_pipe("fork failed", errno);
	if (g_status != 0)
		get_out_of_pipe();
	if (pids[i] == 0)
		execute_comand_in_pipe(sh, i, in_fd, pipefd);
	close(pipefd[1]);
	if (in_fd != 0)
		close(in_fd);
	in_fd = pipefd[0];
}

void	execute_pipeline(t_sh *sh, int i)
{
	int		in_fd;
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * sh->vars.pipe_num + 1);
	i = 0;
	in_fd = 0;
	prep_cmds_pipes(sh);
	if (filter_cmd_error(sh) == true)
		return ;
	ft_sigset_pipes();
	while (i < sh->vars.pipe_num)
	{
		handle_redirects(sh, i);
		pipeline_helper(sh, i, pids, in_fd);
		i++;
	}
	finish_pipeline(sh, pids, in_fd);
	free(pids);
}

void	check_pipes(t_sh *sh)
{
	int	i;

	sh->vars.pipe_num = 0;
	sh->vars.is_pipe = false;
	i = 0;
	while (i < sh->vars.tk_num - 1)
	{
		if (ft_strncmp(sh->tokens[i].tokens, "|", \
			ft_strlen(sh->tokens[i].tokens)) == 0)
		{
			sh->vars.pipe_num++;
			sh->vars.is_pipe = true;
		}
		i++;
	}
	if (sh->vars.is_pipe)
		execute_pipeline(sh, i);
}