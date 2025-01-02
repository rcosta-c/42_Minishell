/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:06 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/01 23:21:22 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_invalid_token(t_sh *sh, int x)
{
	if (sh->tokens[x].cmd == false && sh->tokens[x].arg == false
		&& sh->tokens[x].pipe == false && sh->tokens[x].r_in == false
		&& sh->tokens[x].r_out == false && sh->tokens[x].r_heredoc == false
		&& sh->tokens[x].r_outappend == false && sh->tokens[x].s_quote == false
		&& sh->tokens[x].d_quote == false && sh->tokens[x].f_quote == false
		&& sh->tokens[x].envp == false && sh->tokens[x].file == false
		&& sh->tokens[x].exp_e == false && sh->tokens[x].exp_t == false
		&& sh->tokens[x].exp_empty == false)
		return (true);
	else
		return (false);
}

int	parse_pipes(t_sh *sh, int x, int n_cmd)
{
	if (sh->vars.pipe_num == 0)
		return (x);
	if (sh->tokens[x].pipe)
	{
		sh->comands[n_cmd].pipes = true;
		x++;
	}
	return (x);
}

void	fill_parser(t_sh *sh)
{
	int	x;
	int	n_cmd;

	x = 0;
	n_cmd = 0;
	if (sh->vars.sh_status == false)
		return ;
	while (x < sh->vars.tk_num)
	{
		if (ft_invalid_token(sh, x) == true)
		{
			while (x < sh->vars.tk_num && ft_invalid_token(sh, x) == true)
				x++;
			if (x >= sh->vars.tk_num - 1)
				break ;
		}
		if (sh->tokens[x].exp_empty == true)
			if (++x == sh->vars.tk_num)
				ft_easyfix_command(sh, n_cmd);
		x = parse_utils(sh, x, n_cmd);
		if (x >= sh->vars.tk_num - 1)
			break ;
		x = parse_pipes(sh, x, n_cmd);
		n_cmd++;
	}
}
