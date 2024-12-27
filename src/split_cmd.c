/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:53:06 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/27 08:29:12 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int    split_quote(t_sh *sh, int x, int n)
{
    int len;
    int xx;

    xx = 0;  
    len = check_type_quote(sh->cmd_line, x) - x;
	sh->tokens[n].tokens = malloc(sizeof(char *) * (len + 1));
	while(xx < len)
	{
		sh->tokens[n].tokens[xx] = sh->cmd_line[x];
		x++;
		xx++;
    }
	sh->tokens[n].tokens[xx] = '\0';
    return(x);
}

static int	len_for_split_cicle(t_sh *sh, int x)
{
	int len;
	bool sign;
	
	len = 0;
	sign = false;
	while(sh->cmd_line[x] && sh->cmd_line[x] != ' ')
	{
		if(sh->cmd_line[x] == 34)
			sign = check_if_dquote(sh->cmd_line, x);
		if(sh->cmd_line[x] == 39)
			sign = check_if_squote(sh->cmd_line, x);
		len++;
		x++;
		if(sign == true && sh->cmd_line[x] == ' ')
			while(sh->cmd_line[x] == ' ')
			{
				x++;
				len++;
			}
	}
	return(len);
}

static int  split_cicle(t_sh *sh, int x, int n)
{
    int 	xx;
    int 	len;
	bool	sign;

	xx = 0;
	sign = false;
	len = len_for_split_cicle(sh, x);
   	sh->tokens[n].tokens = malloc(sizeof(char *) * (len + 1));
	while(sh->cmd_line[x] && sh->cmd_line[x] != ' ')
	{
		if(sh->cmd_line[x] == 34)
			sign = check_if_dquote(sh->cmd_line, x);
		if(sh->cmd_line[x] == 39)
			sign = check_if_squote(sh->cmd_line, x);
		sh->tokens[n].tokens[xx++] = sh->cmd_line[x++];
		if(sign == true && sh->cmd_line[x] == ' ')
			while(sh->cmd_line[x] == ' ')
				sh->tokens[n].tokens[xx++] = sh->cmd_line[x++];
	}
	sh->tokens[n].tokens[xx] = '\0';
    return(x);
}

void	split_cmd(t_sh *sh)
{
	int x;
	int n;

	n = 0;
	x = 0;
	if(sh->vars.sh_status == false)
		return;
	if(sh->vars.tk_num == 0)
		return;
	while(1)
	{
		if(!sh->cmd_line[x])
			break;
		if(check_if_squote(sh->cmd_line, x) || check_if_dquote(sh->cmd_line, x))
            x = split_quote(sh, x, n++);
		else
              x = split_cicle(sh, x, n++);
	    if(!sh->cmd_line[x])
			break;
		x++;  
	}
}
