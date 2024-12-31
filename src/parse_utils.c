/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:13 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 21:48:44 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_if_redir(t_sh *sh, int x)
{
	if (sh->tokens[x].r_in == true && sh->tokens[x + 1].file == false)
		return (false);
	else if (sh->tokens[x].r_out == true && sh->tokens[x + 1].file == false)
		return (false);
	else if (sh->tokens[x].r_heredoc == true && !sh->tokens[x + 1].tokens)
		return (false);
	else if (sh->tokens[x].r_outappend == true
		&& sh->tokens[x + 1].file == false)
		return (false);
	else if (sh->tokens[x].r_in == true && sh->tokens[x + 1].file == true)
		return (true);
	else if (sh->tokens[x].r_out == true && sh->tokens[x + 1].file == true)
		return (true);
	else if (sh->tokens[x].r_heredoc == true && sh->tokens[x + 1].tokens)
		return (true);
	else if (sh->tokens[x].r_outappend == true
		&& sh->tokens[x + 1].file == true)
		return (true);
	else
		return (false);
}

int	parse_with_args(t_sh *sh, int n_cmd, int x)
{
	int	narg;
	int	xtemp;

	narg = 0;
	xtemp = x;
	sh->comands[n_cmd].arg = malloc(sizeof(char **) * \
		(sh->comands[n_cmd].n_args + 2));
	sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x - 1].tokens);
	sh->comands[n_cmd].arg[narg++] = ft_strdup(sh->tokens[x - 1].tokens);
	while (sh->tokens[x].pipe == false && x < sh->vars.tk_num)
	{
		if (sh->tokens[x].arg == true)
			sh->comands[n_cmd].arg[narg++] = ft_strdup(sh->tokens[x].tokens);
		x++;
	}
	if (sh->comands[n_cmd].n_args > 0)
		sh->comands[n_cmd].arg[narg] = NULL;
	else
		sh->comands[n_cmd].arg[1] = NULL;
	x = xtemp;
	x = ft_parse_redirs(sh, x, n_cmd);
	x++;
	return (x);
}

int	parse_no_args(t_sh *sh, int n_cmd, int x)
{
	if (ft_strncmp("history", sh->tokens[x].tokens,
			ft_strlen(sh->tokens[x].tokens)) == 0)
	{
		sh->comands[n_cmd].arg = malloc(sizeof(char **) * 3);
		sh->comands[n_cmd].cmd = ft_strdup("cat");
		sh->comands[n_cmd].arg[0] = ft_strdup("cat");
		sh->comands[n_cmd].arg[1] = ft_strjoin(sh->vars.minihome, "/.history");
		sh->comands[n_cmd].arg[2] = NULL;
		sh->comands[n_cmd].n_args = 1;
		x++;
	}
	else
	{
		sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2);
		sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x].tokens);
		sh->comands[n_cmd].arg[0] = ft_strdup(sh->tokens[x].tokens);
		sh->comands[n_cmd].arg[1] = NULL;
		sh->comands[n_cmd].n_args = 0;
		x++;
	}
	x = ft_parse_redirs(sh, x, n_cmd);
	return (x);
}

int	parse_no_cmds(t_sh *sh, int n_cmd, int x)
{
	int	narg;

	narg = 0;
	sh->vars.cmds_num = 1;
	init_cmds(sh, n_cmd);
	sh->comands[n_cmd].arg = malloc(sizeof(char **) * (sh->vars.tk_num + 1));
	sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x].tokens);
	if (sh->vars.tk_num > 1)
	{
		while (x < sh->vars.tk_num)
			sh->comands[n_cmd].arg[narg++] = ft_strdup(sh->tokens[x++].tokens);
		sh->comands[n_cmd].arg[narg] = NULL;
		sh->comands[n_cmd].n_args = narg - 1;
		x++;
	}
	else
	{
		sh->comands[n_cmd].arg[0] = ft_strdup(sh->tokens[x].tokens);
		sh->comands[n_cmd].arg[1] = NULL;
		sh->comands[n_cmd].n_args = 0;
		x++;
	}
	return (x);
}

int	parse_utils(t_sh *sh, int x, int n_cmd)
{
	int	xtemp;

	if (x == sh->vars.tk_num)
		return (x);
	if (sh->tokens[x].cmd)
	{
		xtemp = x;
		while (x < sh->vars.tk_num && sh->tokens[x].pipe == false)
		{
			if (sh->tokens[x].arg == true)
				sh->comands[n_cmd].n_args++;
			x++;
		}
		x = xtemp;
		if (x < sh->vars.tk_num && sh->comands[n_cmd].n_args >= 1)
		{
			x++;
			x = parse_with_args(sh, n_cmd, x);
		}
		else
			x = parse_no_args(sh, n_cmd, x);
	}
	else
		x = parse_no_cmds(sh, n_cmd, x);
	return (x);
}
