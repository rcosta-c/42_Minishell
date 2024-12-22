/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:06 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/21 16:46:14 by rcosta-c         ###   ########.fr       */
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
/*static int	parse_emptyenv(t_sh *sh, int x, int n_cmd)
{
	sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2); 
	sh->comands[n_cmd].cmd = ft_strdup("echo"); 
	sh->comands[n_cmd].arg[0] = ft_strdup("echo");
	sh->comands[n_cmd].arg[1] = NULL;
	sh->comands[n_cmd].n_args = 0;
	x++;
	return(x);
	
}*/

/*
static bool	ft_token_hash_flag(t_sh *sh, int x)
{
	int	len;

	len = ft_strlen(sh->tokens[x].tokens);
	if(len == 1 && sh->tokens[x].tokens[0] == '$')
		return(true);
	else
		return(false);
}*/

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
		if(sh->tokens[x].exp_empty == true)// || ft_token_hash_flag(sh, x) == true)
		{
//printf("\naquitambemestuouad!!!!\n");
			//x = parse_emptyenv(sh, x, n_cmd);
			x++;
			if(x == sh->vars.tk_num)
			{
				sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2); 
				sh->comands[n_cmd].cmd = ft_strdup("echo"); 
				sh->comands[n_cmd].arg[0] = ft_strdup("echo");
				sh->comands[n_cmd].arg[1] = NULL;
				sh->comands[n_cmd].n_args = 0;
				return;
			}
		}
/*		if(ft_strncmp((sh->tokens[x].tokens), "history", 8) == 0)
			{
				sh->comands[n_cmd].arg = malloc(sizeof(char **) * 3); 
				sh->comands[n_cmd].cmd = ft_strdup("echo"); 
				sh->comands[n_cmd].arg[0] = ft_strdup("echo");
				sh->comands[n_cmd].arg[1] = ft_strdup(add_history);;
				sh->comands[n_cmd].arg[2] = NULL;
				sh->comands[n_cmd].n_args = 0;
				return;
			} */
	//	else
	//	{
//		printf("\n\nx vai em =%d\n\n", x);
		x = parse_utils(sh, x, n_cmd);
//		printf("\n\nx vai em =%d\n\n", x);
		if(x >= sh->vars.tk_num)
			break;
		x = parse_pipes(sh, x, n_cmd);
	//	}
		n_cmd++;		
	}
}

