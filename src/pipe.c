/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:05:19 by cde-paiv          #+#    #+#             */
/*   Updated: 2024/12/11 18:27:27 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// funcao para criar os pipes
void	create_pipes(t_sh *sh, int ***pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * sh->vars.pipe_num);
	if (!*pipes)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < sh->vars.pipe_num)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
			exit(EXIT_FAILURE);
		if (pipe((*pipes)[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	close_pipes(int **pipes, int pipe_num)
{
	int	i;

	i = 0;
	while (i < pipe_num)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	setup_pipes(int **pipes, int i, int cmds_num)
{
	int	j;

	if (i == 0)
		dup2(pipes[i][1], STDOUT_FILENO);
	else if (i == cmds_num - 1)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	j = 0;
	while (j < cmds_num - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	execute_pipeline(t_sh *sh, int n_cmds)
{
	int	i;
	int	pipefd[2];
	int	in_fd;

	in_fd = 0;
	i = 0;
	while (i < n_cmds)
	{
		handle_redirects(sh, i);
		pipe(pipefd);
		if (fork() == 0)
		{
			dup2(in_fd, 0);
			if (i < n_cmds - 1)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			execvp(sh->comands[i].cmd, sh->comands[i].arg);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
		in_fd = pipefd[0];
		i++;
	}
	i = 0;
	while (i < n_cmds)
	{
		wait(NULL);
		i++;
	}
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
		execute_pipeline(sh, sh->vars.cmds_num);
}
