/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:52:16 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/22 08:53:05 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	filter_args(t_sh *sh, int n)
{
	if(n == 0)
		return;
	if(sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false \
		&& sh->tokens[n].r_in == false && sh->tokens[n].r_out == false && \
		sh->tokens[n].r_heredoc == false && sh->tokens[n].r_outappend == false && \
		sh->tokens[n].pipe == false && sh->tokens[n].file == false && \
		sh->tokens[n].exp_e == false && sh->tokens[n].f_quote == false && \
		sh->tokens[n].exp_t == false && sh->tokens[n].r_outappend == false)
		{
			sh->tokens[n].arg = true;
		}
	if(sh->tokens[n].d_quote == true || sh->tokens[n].s_quote == true)
		sh->tokens[n].arg = true;
	if(sh->tokens[n].exp_e == true || sh->tokens[n].exp_t == true)
		sh->tokens[n].arg = true;
	if(sh->tokens[n].file == true)
		sh->tokens[n].arg = true;
}

void	filter_envp(t_sh *sh, int n)
{
	int	x;

	if(!sh->tokens[n].tokens)
		return;
	if(sh->tokens[n].tokens[0] == '$')
	{
		x = 1;
		while((sh->tokens[n].tokens[x] >= 'A' && sh->tokens[n].tokens[x] <= 'Z') || \
		sh->tokens[n].tokens[x] == '$' || sh->tokens[n].tokens[x] == '?')
			x++;
		if(!sh->tokens[n].tokens[x])
			sh->tokens[n].exp_e = true;
		else
			sh->tokens[n].f_quote = true;
	}
	if(sh->tokens[n].tokens[0] == '~')
	{
		if(!sh->tokens[n].tokens[1] || sh->tokens[n].tokens[1] == '/')
			sh->tokens[n].exp_t = true;	
	}
}

void	filter_cmds(t_sh *sh, int n)
{
	if(n == 0 && sh->tokens[n].pipe == false && \
		sh->tokens[n].r_out == false && sh->tokens[n].r_in == false && \
		sh->tokens[n].s_quote == false)
		{
//			printf("\n\nAQUI ENTRIOU!!\n\n");
			sh->tokens[n].cmd = true;
			sh->tokens[n].arg = false;
			sh->vars.cmds_num++;
		}
	else if(n > 0 && sh->tokens[n - 1].pipe == true &&
			sh->tokens[0].pipe == false)
	{
//		printf("\n\nAQUI TAMBEEEM ENTRIOU!!\n\n");
		sh->tokens[n].cmd = true;
		sh->tokens[n].arg = false;
		sh->vars.cmds_num++;

	}
}

void	filter_tokens(t_sh *sh)
{
	int	n;

	n = 0;
	while(n < sh->vars.tk_num)
	{
		if(!sh->tokens[n].tokens)
		return;
		filter_quotes(sh, n);
		filter_envp(sh, n);
		filter_file(sh, n);
		filter_pipes_redir(sh, n);
		filter_args(sh, n);
		filter_cmds(sh, n);
	n++;
	}
}

