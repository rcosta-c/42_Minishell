/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:37 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/08 23:33:35 by rcosta-c         ###   ########.fr       */
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
	int	x;

	if (sh->vars.tk_num == 0)
		return ;
	x = 0;
	sh->tokens = malloc(sizeof(t_tokens) * (sh->vars.tk_num + 2));
	if (!sh->tokens)
		exit(EXIT_FAILURE);
	while (x <= sh->vars.tk_num)
	{
		sh->tokens[x].num = x;
		init_tk_flag1(sh, x);
		x++;
	}
}

void	init_parser(t_sh *sh)
{
	int	x;

	if (sh->vars.cmds_num == 0 && sh->vars.pipe_num == 0
		&& sh->vars.redir_tot == 0)
		return ;
	x = 0;
	sh->comands = malloc(sizeof(t_exec) * (sh->vars.cmds_num + 1));
	if (!sh->comands)
		exit(EXIT_FAILURE);
	while (x < sh->vars.cmds_num)
	{
		init_cmds(sh, x);
		x++;
	}
}

void	init_cycle(t_sh *sh)
{
	sh->vars.sh_status = true;
	ft_sigset();
	init_vars(sh);
	if (sh->cmd_line)
		free(sh->cmd_line);
}

int	init_check_invalid_start(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.tk_num && (sh->tokens[x].d_quote == true
			|| sh->tokens[x].s_quote == true)
		&& ft_strlen(sh->tokens[x].tokens) == 2)
	{
		x++;
	}
	return (x);
}
