/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:05:19 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/03 23:39:14 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_comand_in_pipe(t_sh *sh, int i, int in_fd, int pipefd[2])
{
	struct stat file_info;
	int 		xx;

	xx = 0;
	dup2(in_fd, STDIN_FILENO);
	if (i < sh->vars.cmds_num - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (check_if_builtin(sh->comands[i].cmd))
	{
		exec_builtin(sh, i);
		exit(g_status);
	}
	else if (execve(sh->comands[i].cmd, sh->comands[i].arg, sh->envp) == -1)
	{
		perror("Erro ao executar comando");
		exit(EXIT_FAILURE);
	}
	while(sh->comands[i].n_args >= 1 && xx < sh->comands[i].n_args)
	{
		if (stat(sh->comands[i].arg[xx + 1], &file_info) == -1)
			if (errno == ENOENT)
				exit(EXIT_FAILURE);
		xx++;
	}
}


void	execute_pipeline(t_sh *sh, int i)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;

	i = 0;
	in_fd = 0;
	prep_cmds_pipes(sh);
	if (filter_cmd_error(sh) == true)
		return ;
	while (i < sh->vars.cmds_num)
	{
		handle_redirects(sh, i);
		pipe(pipefd);
		pid = fork();
		if (pid == -1 || g_status)
			get_out_of_pipe();
		if (pid == 0)
			execute_comand_in_pipe(sh, i, in_fd, pipefd);
		close(pipefd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = pipefd[0];
		i++;
	}
	pipeline_exit(sh, in_fd, i);
}

void	check_pipes(t_sh *sh)
{
	int	i;

	sh->vars.pipe_num = 0;
	sh->vars.is_pipe = false;
	i = 0;
	while (i < sh->vars.tk_num - 1)
	{
		if (strcmp(sh->tokens[i].tokens, "|") == 0)
		{
			sh->vars.pipe_num++;
			sh->vars.is_pipe = true;
		}
		i++;
	}
	if (sh->vars.is_pipe)
		execute_pipeline(sh, i);
}
