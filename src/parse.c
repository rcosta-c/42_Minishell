/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:06 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/13 10:54:07 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_r_append_out(t_sh *sh)
{
	int x;

	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].r_outappend)
		{
			x++;
			if(sh->tokens[x].file)
				return(false);
			else
				return(true);		
		}
		x++;
	}
	return(false);
}

bool    check_r_out(t_sh *sh)
{
	int	x;

	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].r_out)
		{
			x++;
			if(sh->tokens[x].file)
				return(false);
			else
				return(true);		
		}
		x++;
	}
	return(false);
}

bool    check_r_in(t_sh *sh)
{
	int	x;

	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].r_in)
		{
			x++;
			if(sh->tokens[x].file)
				return(false);
			else
				return(true);		
		}
		x++;
	}
	return(false);
}

bool    check_before_parse(t_sh *sh)
{
	int x;

	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].f_quote)
			return(true);
		x++;
	}
	return(false);
}

void    fill_parser(t_sh *sh)
{
	int x;
	int n_cmd;

	if(sh->vars.sh_status == false)
		return;
	x = 0;
	n_cmd = 0;
	remove_quoted(sh);
	while(x < sh->vars.tk_num)
	{
		x = parse_utils(sh, x, n_cmd);
		if(x >= sh->vars.tk_num)
			break;
		x = parse_pipes(sh, x, n_cmd);
		n_cmd++;		
	}
}

