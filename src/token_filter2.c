/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:52:02 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/22 09:15:12 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	filter_file(t_sh *sh, int n)
{
	int	x;

	x = 0;
	while(sh->tokens[n].tokens[x])
	{
		if(sh->tokens[n].tokens[x] == '.')
		{
			if(sh->tokens[n].tokens[x + 1] == '.')
				break;
			sh->tokens[n].file = true;
			break;
		}
		x++;
	}
	if(n > 0 && sh->tokens[n - 1].r_heredoc == true)
	{
		sh->tokens[n].file = true;
		sh->tokens[n].arg = false;
	}
}

static void	check_filter_redir(t_sh *sh, int n)
{
	if(sh->tokens[n].tokens[0] == '>')
	{
		if(!sh->tokens[n].tokens[1])
		{
		sh->tokens[n].r_out = true;
			sh->vars.redir_num++;
		}
		if(sh->tokens[n].tokens[1] == '>')
		{
			sh->tokens[n].r_outappend = true;
			sh->vars.redir_num++;
		}
	}
}

void	filter_pipes_redir(t_sh *sh, int n)
{
	if(sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false)
	{
		if(sh->tokens[n].tokens[0] == '|')
			{
				sh->tokens[n].pipe = true;
				sh->vars.pipe_num++;
			}
		if(sh->tokens[n].tokens[0] == '<')
		{
			if(!sh->tokens[n].tokens[1])
			{
				sh->tokens[n].r_in = true;
				sh->vars.redir_num++;
			}
			if(sh->tokens[n].tokens[1] == '<')
			{
				sh->tokens[n].r_heredoc = true;
				sh->vars.redir_num++;
				sh->vars.heredoc_num++;
			}
		}
		check_filter_redir(sh, n);
	}
}

void	filter_quotes(t_sh *sh, int n)
{
	int len;
	int	counter;
	int x;
	
	x = 0;
	counter = 0;
	len = ft_strlen(sh->tokens[n].tokens);
	if(sh->tokens[n].tokens[x] == 34)
	{
		while(sh->tokens[n].tokens[x++])
		{
			if(sh->tokens[n].tokens[x] == '$')
				sh->tokens[n].exp_e = true;
			if(sh->tokens[n].tokens[x] == 34)
				counter++;
		}
//		printf("\n\nCOUNTER=%d\n\n", counter);
		if(counter == 1)			//(sh->tokens[n].tokens[len - 1] == 34 && len > 1)
			sh->tokens[n].d_quote = true;
		else
			sh->tokens[n].f_quote = true;
	}
	else if(sh->tokens[n].tokens[x] == 39)
	{
		if(sh->tokens[n].tokens[len - 1] == 39 && len > 1)
			sh->tokens[n].s_quote = true;
		else
			sh->tokens[n].f_quote = true;
	}
}
/*
void	filter_quotes(t_sh *sh, int n)
{
	int	counter_d;
	int counter_s;
	int	x;
	
	x = 0;
	counter_d = 0;
	counter_s = 0;
	while(sh->tokens[n].tokens[x])
	{
		if(sh->tokens[n].tokens[x] == '$')
			sh->tokens[n].exp_e = true;
		if(sh->tokens[n].tokens[x] == 34)
			counter_d++;
		if(sh->tokens[n].tokens[x] == 39)
			counter_s++;
		x++;
	}
	if(counter_d == 2)
	{
		sh->tokens[n].d_quote = true;
		return;
	}
	else if(counter_s == 2)
	{
		sh->tokens[n].s_quote = true;
		return;
	}
	else
			sh->tokens[n].f_quote = true;
}
*/
/*
void	filter_quotes(t_sh *sh, int n, int x)
{
	int	counter_d;
	int	counter_s;
	
	counter_d = 0;
	counter_s = 0;
	if(ft_strlen(sh->tokens[n].tokens) < 2)
		return;
	while(sh->tokens[n].tokens[x])
	{
		if(sh->tokens[n].tokens[x] == '$')
			sh->tokens[n].exp_e = true;
		if(sh->tokens[n].tokens[x] == 34)
			counter_d++;
		x++;
	}
//printf("\n\nCOUNTER=%d\n\n", counter_d);
	if(counter_d == 2)			//(sh->tokens[n].tokens[len - 1] == 34 && len > 1)
		sh->tokens[n].d_quote = true;
	else
		sh->tokens[n].f_quote = true;
	if(counter_s == 2)
		sh->tokens[n].s_quote = true;
	else
		sh->tokens[n].f_quote = true;
	
}*/
