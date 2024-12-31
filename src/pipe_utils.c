/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:54:31 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 21:57:29 by rcosta-c         ###   ########.fr       */
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
	perror("Erro ao criar processo");
	exit(EXIT_FAILURE);
}

void	pipeline_exit(t_sh *sh, int in_fd, int i)
{
	close(in_fd);
	i = 0;
	while (i < sh->vars.cmds_num)
	{
		wait(NULL);
		i++;
	}
}
