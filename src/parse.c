/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:06 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 18:08:51 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_r_append_out(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.tk_num)
	{
		if (sh->tokens[x].r_outappend)
		{
			x++;
			if (sh->tokens[x].file)
				return (false);
			else
				return (true);
		}
		x++;
	}
	return (false);
}

bool	check_r_out(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.tk_num)
	{
		if (sh->tokens[x].r_out)
		{
			x++;
			if (sh->tokens[x].file)
				return (false);
			else
				return (true);
		}
		x++;
	}
	return (false);
}

bool	check_r_in(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.tk_num)
	{
		if (sh->tokens[x].r_in)
		{
			x++;
			if (sh->tokens[x].file)
				return (false);
			else
				return (true);
		}
		x++;
	}
	return (false);
}

bool	check_before_parse(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.tk_num)
	{
		if (sh->tokens[x].f_quote)
			return (true);
		x++;
	}
	return (false);
}

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

void	fill_parser(t_sh *sh)
{
	int	x;
	int	n_cmd;

	if (sh->vars.sh_status == false)
		return ;
	x = 0;
	n_cmd = 0;
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
		{
			x++;
			if (x == sh->vars.tk_num)
			{
				sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2);
				sh->comands[n_cmd].cmd = ft_strdup("echo");
				sh->comands[n_cmd].arg[0] = ft_strdup("echo");
				sh->comands[n_cmd].arg[1] = NULL;
				sh->comands[n_cmd].n_args = 0;
				return ;
			}
		}
		x = parse_utils(sh, x, n_cmd);
		if (x >= sh->vars.tk_num - 1)
			break ;
		x = parse_pipes(sh, x, n_cmd);
		n_cmd++;
	}
}
