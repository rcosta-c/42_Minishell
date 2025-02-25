/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:52:16 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/18 11:40:31 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	filter_args(t_sh *sh, int n)
{
	if (n == 0)
		return ;
	filter_args_checker(sh, n);
	if ((sh->tokens[n].d_quote == true || sh->tokens[n].s_quote == true)
		&& sh->tokens[n - 1].r_in == false
		&& sh->tokens[n - 1].r_out == false
		&& sh->tokens[n - 1].r_heredoc == false
		&& sh->tokens[n - 1].r_outappend == false)
		sh->tokens[n].arg = true;
	else if (sh->tokens[n].exp_e == true
		|| sh->tokens[n].exp_t == true)
		sh->tokens[n].arg = true;
	else if (sh->tokens[n].file == true
		&& (sh->tokens[n - 1].r_outappend == false)
		&& (sh->tokens[n - 1].r_in == false)
		&& (sh->tokens[n - 1].r_out == false)
		&& (sh->tokens[n - 1].r_heredoc == false))
	{
		sh->tokens[n].file = false;
		sh->tokens[n].arg = true;
	}
}

void	filter_envp(t_sh *sh, int n)
{
	int		x;

	if (!sh->tokens[n].tokens)
		return ;
	x = 0;
	while (sh->tokens[n].tokens[x])
	{
		if (sh->tokens[n].tokens[x] == '$')
			x = filter_envp_helper(sh, n, x);
		else if (sh->tokens[n].tokens[x] == '~')
		{
			if (!sh->tokens[n].tokens[++x] || sh->tokens[n].tokens[x] == '/')
				sh->tokens[n].exp_t = true;
		}
		else
			x++;
	}
}

void	filter_cmds(t_sh *sh, int n)
{
	if (n == 0 && sh->tokens[n].pipe == false
		&& sh->tokens[n].r_out == false
		&& sh->tokens[n].r_in == false
		&& sh->tokens[n].r_heredoc == false
		&& sh->tokens[n].r_outappend == false)
	{
		sh->tokens[n].cmd = true;
		sh->tokens[n].arg = false;
		sh->vars.cmds_num++;
	}
	else if (n > 0 && sh->tokens[n - 1].pipe == true
		&& sh->tokens[0].pipe == false)
	{
		sh->tokens[n].cmd = true;
		sh->tokens[n].arg = false;
		sh->vars.cmds_num++;
	}
}

void	filter_tokens(t_sh *sh)
{
	int	n;

	n = 0;
	while (n < sh->vars.tk_num)
	{
		if (!sh->tokens[n].tokens)
			return ;
		filter_envp(sh, n);
		filter_quotes(sh, n);
		filter_file(sh, n);
		filter_pipes_redir(sh, n);
		filter_args(sh, n);
		filter_cmds(sh, n);
		n++;
	}
}
