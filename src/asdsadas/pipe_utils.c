/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:54:31 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/20 23:31:26 by rcosta-c         ###   ########.fr       */
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
