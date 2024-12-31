/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:42:59 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 21:49:24 by rcosta-c         ###   ########.fr       */
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

void	ft_easyfix_command(t_sh *sh, int n_cmd)
{
	sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2);
	sh->comands[n_cmd].cmd = ft_strdup("echo");
	sh->comands[n_cmd].arg[0] = ft_strdup("echo");
	sh->comands[n_cmd].arg[1] = NULL;
	sh->comands[n_cmd].n_args = 0;
	return ;
}
