/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 23:21:44 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 23:26:00 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_count_redirs(t_sh *sh, int x, int n_cmd)
{
	while (x < sh->vars.tk_num && sh->tokens[x].pipe == false)
	{
		if (sh->tokens[x].r_in == true
			|| sh->tokens[x].r_heredoc == true
			|| sh->tokens[x].r_out == true
			|| sh->tokens[x].r_outappend == true)
		{
			sh->comands[n_cmd].n_redir++;
		}
		x++;
	}
}

static int	ft_parse_redirs_in(t_sh *sh, int x, int n_cmd, int counter)
{
	if (sh->tokens[x - 1].r_in == true)
	{
		if (sh->comands[n_cmd].heredoc == true)
			sh->comands[x].heredoc = false;
		if (sh->comands[n_cmd].infile != NULL)
			free(sh->comands[n_cmd].infile);
		if (sh->tokens[x].file == true)
			sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	else if (sh->tokens[x - 1].r_heredoc == true)
	{
		sh->comands[n_cmd].heredoc = true;
		if (sh->comands[n_cmd].infile != NULL)
			free(sh->comands[n_cmd].infile);
		if (sh->tokens[x].tokens)
			sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	return (counter);
}

static int	ft_parse_redirs_out(t_sh *sh, int x, int n_cmd, int counter)
{
	if (sh->tokens[x - 1].r_out == true)
	{
		if (sh->comands[n_cmd].outfile != NULL)
			free(sh->comands[n_cmd].outfile);
		if (sh->tokens[x].file == true)
			sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	else if (sh->tokens[x - 1].r_outappend == true)
	{
		if (sh->comands[n_cmd].outappendfile != NULL)
			free(sh->comands[n_cmd].outappendfile);
		if (sh->tokens[x].file == true)
			sh->comands[n_cmd].outappendfile = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	return (counter);
}

int	ft_parse_redirs(t_sh *sh, int x, int n_cmd)
{
	int	counter;

	if (x >= sh->vars.tk_num)
		return (x);
	ft_count_redirs(sh, x, n_cmd);
	if (sh->comands[n_cmd].n_redir > 0)
	{
		counter = 0;
		sh->comands[n_cmd].redir = true;
		while (counter < sh->comands[n_cmd].n_redir && x < sh->vars.tk_num)
		{
			counter = ft_parse_redirs_in(sh, x, n_cmd, counter);
			counter = ft_parse_redirs_out(sh, x, n_cmd, counter);
			x++;
		}
	}
	return (x);
}
