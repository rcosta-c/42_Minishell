/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:54:31 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/11 18:02:23 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_cmds_pipes(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.cmds_num)
	{
		sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
		x++;
	}
}

void	get_out_of_pipe(void)
{
	perror("Error while creating process");
	exit(EXIT_FAILURE);
}

void	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = 128 + WTERMSIG(status);
	signal(SIGINT, ft_signal_handfd);
	signal(SIGQUIT, SIG_IGN);
}

void handle_error_pipe(const char *msg, int exit_code)
{
    perror(msg);
    exit(exit_code);
}
