/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:51:45 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/18 10:02:18 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens(t_sh *sh)
{
	int x;
	int counter;

	x = 0;
	counter = 0;
	if(!sh->cmd_line)
		return(counter);
	while(sh->cmd_line[x])
	{
		while(sh->cmd_line[x] == 32)
			x++;
		if(sh->cmd_line[x] == 34 || sh->cmd_line[x] == 39)
		{
			x = check_type_quote(sh->cmd_line, x);
			counter++;
		}
		while(counter_validation(sh->cmd_line[x]))
			x++;
		if(sh->cmd_line[x] == 32 && counter_validation(sh->cmd_line[x - 1]))
			counter++;
		if(!sh->cmd_line[x] && counter_validation(sh->cmd_line[x - 1]))
			counter++;
	}
	return(counter);
}

bool counter_validation(int c)
{
	if(c == 33 || (c >= 35 && c <= 38) || (c >= 40 && c <= 176))
		return(true);
	else 
		return(false);
}

static bool	check_if_special_redirin(char *str, int x)
{
	if(str[x] == '<')
	{
		if(str[x + 2] && str[x + 1] == '<' && ft_isprint(str[x + 2]))
			return(true);
		else if(str[x + 1] && ft_isprint(str[x + 1]))
			return(true);
		else
			return(false);
	}
	return(false);
}

static bool	check_if_special_redirout(char *str, int x)
{
	if(str[x] == '>')
	{
		if(str[x + 2] && str[x + 1] == '>' && ft_isprint(str[x + 2]))
			return(true);
		else if(str[x + 1] && ft_isprint(str[x + 1]))
			return(true);
		else
			return(false);
	}
	return(false);
}

static bool	check_if_special_redir(char *str, int x)
{
	
	if (check_if_special_redirin(str, x) == true)
		return(true);
	else if (check_if_special_redirout(str, x) == true)
		return(true);
	else
		return(false);
}

static void	ft_special_agent_redir(char *str, char *temp, int *x_o, int *x_d)
{
//printf("\nseu cabrao!\n");
	if(str[*x_o] == '>' || str[*x_o] == '<')
	{
		if(*x_o > 0 && ft_isalnum(str[*x_o - 1]))
			temp[(*x_d)++] = ' ';
		temp[(*x_d)++] = str[(*x_o)++];
		if(str[*x_o] == '>' || str[*x_o] == '<')
		{
			temp[(*x_d)++] = str[(*x_o)++];
			temp[(*x_d)++] = ' ';
		}
		else
			temp[(*x_d)++] = ' ';
		if(str[*x_o] == 32)
			(*x_o)++;
		return;
	}	
}

static void ft_give_some_space(char *str, char *temp, int *x_o, int *x_d)
{
	while(str[*x_o] == 32)
			(*x_o)++;
	if(str[*x_o] != '\0' && *x_d > 0)
		temp[(*x_d)++] = 32;	
}

static bool check_if_pipe(char *str,int x_o)
{
	if(str[x_o] == '|')
		return(true);
	else
		return(false);
}

static void ft_call_plumber(char *str, char *temp, int *x_o, int *x_d)
{
	if(str[*x_o] == 32)
		ft_give_some_space(str, temp, &x_o[0], &x_d[0]);
	if(*x_o > 0)
	{
		if(str[*x_o - 1] != ' ')
			temp[(*x_d)++] = ' ';
	}
	temp[(*x_d)++] = str[(*x_o)++];
//	if(str[*x_o] == 32)
//	{
//		(*x_o)++;
//		temp[(*x_d)++] = ' ';
//	}
}

static int process_chunk(char *str, char *temp, int *x_o, int *x_d)
{
	int	max;

	max = ft_strlen(str);
	if(str[*x_o] == 32)
		ft_give_some_space(str, temp, &x_o[0], &x_d[0]);
	if(str[*x_o] == 34 || str[*x_o] == 39)	
	{
		if(check_if_dquote(str, *x_o) || check_if_squote(str, *x_o))
		{	
			temp[(*x_d)++] = str[(*x_o)++];
			while(str[*x_o] != 34 && str[*x_o] != 39)
				temp[(*x_d)++] = str[(*x_o)++];
		}
		else
			temp[(*x_d)++] = str[(*x_o)++];	
	}
	while(str[*x_o] && token_is_valid(str[*x_o]) && *x_o < max)
	{
//printf("\nseu cabrao!\n");
		if(check_if_special_redir(str, *x_o))
			ft_special_agent_redir(str, temp, &x_o[0], &x_d[0]);
		else if(check_if_pipe(str, *x_o) == true)
			ft_call_plumber(str, temp, &x_o[0], &x_d[0]);
		else
			temp[(*x_d)++] = str[(*x_o)++];
	}
	//temp[*x_d++] = ' ';
	if(str[*x_o] == 32)
		ft_give_some_space(str, temp, &x_o[0], &x_d[0]);
	return(*x_o);
}

char *prepare_line(char *str)
{
	int     x_o[1];
	int     x_d[1];
	char    temp[1000];

	x_o[0] = 0;
	x_d[0] = 0;
	if(ft_strlen(str) == 0)
		return(ft_strdup(""));
	while(str[x_o[0]])
		x_o[0] = process_chunk(str, temp, &x_o[0], &x_d[0]);
	temp[x_d[0]] = '\0';
	free(str);
	return(ft_strdup(temp));
}




