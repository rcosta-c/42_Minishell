/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:37 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/16 19:45:05 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_error(t_sh *sh)
{
	sh->error.cmd_error = false;
	sh->error.token_error = false;
	sh->error.expand_error = false;
	sh->error.parse_error = false;
	sh->error.exec_error = false;
}


void	init_tokens(t_sh *sh)
{
	int x;

	if(sh->vars.tk_num == 0)
		return;
	x = 0;
	sh->tokens = malloc(sizeof(t_tokens) * (sh->vars.tk_num + 2));
	if(!sh->tokens)
		exit(EXIT_FAILURE);
	while(x <= sh->vars.tk_num)
	{
		sh->tokens[x].num = x;
		init_tk_flag1(sh, x);
		x++;
	}
}

void	init_parser(t_sh *sh)
{
	int	x;

	if(sh->vars.cmds_num == 0 && sh->vars.pipe_num == 0 && sh->vars.redir_num == 0)
		return;
	x = 0;
	/*if(sh->vars.cmds_num > sh->vars.pipe_num)
		sh->vars.cmds_num = sh->vars.cmds_num;
	else
		sh->vars.cmds_num = 1;*/
	sh->comands = malloc(sizeof(t_exec) * (sh->vars.cmds_num + 1));
	if(!sh->comands)
		exit(EXIT_FAILURE);
	while(x < sh->vars.cmds_num)
	{
		init_cmds(sh, x);
		x++;
	}
}

void init_cycle(t_sh *sh)
{
	sh->vars.sh_status = true;
	ft_sigset();
	init_vars(sh);
	if(sh->cmd_line)
		free(sh->cmd_line);
}
