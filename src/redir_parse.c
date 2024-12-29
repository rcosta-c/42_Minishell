/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:46:16 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/29 23:12:20 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_count_redirs(t_sh *sh, int x, int n_cmd)
{
	while(x < sh->vars.tk_num && sh->tokens[x].pipe == false)
	{
		if(sh->tokens[x].r_in == true || sh->tokens[x].r_heredoc == true
			|| sh->tokens[x].r_out == true || sh->tokens[x].r_outappend == true)
		{
			sh->comands[n_cmd].n_redir++;	
		}
		x++;	
	}	
}

static int	ft_parse_redirs_in(t_sh *sh, int x, int n_cmd, int counter)
{
	if(sh->tokens[x - 1].r_in  == true)
	{
		if(sh->comands[n_cmd].infile != NULL)
			free(sh->comands[n_cmd].infile);
		if(sh->tokens[x].file == true )
			sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	else if(sh->tokens[x - 1].r_heredoc == true)
	{
		if(sh->comands[n_cmd].inheredoc_file != NULL)
			free(sh->comands[n_cmd].inheredoc_file);
		if(sh->tokens[x].tokens)
			sh->comands[n_cmd].inheredoc_file = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	return(counter);

}
static int	ft_parse_redirs_out(t_sh *sh, int x, int n_cmd, int counter)
{
	if(sh->tokens[x - 1].r_out == true)
	{
		if(sh->comands[n_cmd].outfile != NULL)
			free(sh->comands[n_cmd].outfile);
		if(sh->tokens[x].file == true)
			sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	else if(sh->tokens[x - 1].r_outappend == true)
	{
		if(sh->comands[n_cmd].outappendfile != NULL)
			free(sh->comands[n_cmd].outappendfile);
		if(sh->tokens[x].file == true)
			sh->comands[n_cmd].outappendfile = ft_strdup(sh->tokens[x].tokens);
		else
			sh->comands[n_cmd].errors.empty_redir = true;
		counter++;
	}
	return(counter);
}

int     ft_parse_redirs(t_sh *sh, int x, int n_cmd)
{
	int counter;
	
	if(x >= sh->vars.tk_num)
		return(x);
	ft_count_redirs(sh, x, n_cmd);
	if(sh->comands[n_cmd].n_redir > 0)
	{
		counter = 0;
		sh->comands[n_cmd].redir = true;
		while(counter < sh->comands[n_cmd].n_redir && x < sh->vars.tk_num)
		{
			counter = ft_parse_redirs_in(sh, x, n_cmd, counter);
			counter = ft_parse_redirs_out(sh, x, n_cmd, counter);
			x++;
		}
	}
	return(x);    
}

void    ft_redir_multiargs(t_sh *sh)
{
	int		x;
	int		xx;
	int	 	counter;
	char	 *temp;
	
	x = 0;
	counter = 0;
	if(sh->vars.redir_tot == 0 || sh->vars.tk_num < 4)
		return;
	while(x < sh->vars.tk_num)
	{
		
		if(x > 0 && (sh->tokens[x].r_in == true || sh->tokens[x].r_heredoc == true || 
			sh->tokens[x].r_outappend == true || sh->tokens[x].r_out == true))
			{
				counter = 0;
				x++;
				if(sh->tokens[x].d_quote == true || sh->tokens[x].s_quote == true)
				{
					x++;
					counter++;
				}
				while(x < sh->vars.tk_num && (sh->tokens[x].d_quote == true || sh->tokens[x].s_quote == true))
				{
					sh->tokens[x].arg = false;
					sh->tokens[x].d_quote = false;
					sh->tokens[x].s_quote = false;
					x++;
					counter++;
				}
				if(counter > 1)
				{
					xx = 0;
					while(xx < counter)
					{
						temp = ft_strjoin(sh->tokens[x - xx - 1].tokens, sh->tokens[x - xx].tokens);
						free(sh->tokens[x - xx - 1].tokens);
						sh->tokens[x - xx - 1].tokens = ft_strdup(temp);
						free(temp);
						xx++;
					}
				}
			}
		else
			x++;
	}

}
