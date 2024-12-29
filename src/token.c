/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:51:45 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/29 01:04:59 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens(t_sh *sh)
{
	int x;
	int counter;
	int	init;
	int xx;

	xx = 0;
	
	x = 0;
	counter = 0;
	init = 0;
	if (!sh->cmd_line)
		return (0);
	while (sh->cmd_line[x])
	{
		while (sh->cmd_line[x] == ' ')
			x++;
		if (sh->cmd_line[x] == '"' || sh->cmd_line[x] == '\'')
		{
			xx = 0;
			init = x;
			x = check_type_quote(sh->cmd_line, x);
			while(init < x)
			{
				sh->temp[counter][xx] = sh->cmd_line[init];
				xx++;
				init++;
			}
			sh->temp[counter][xx] = '\0';
			counter++; 
		}
		else if (sh->cmd_line[x] && sh->cmd_line[x] != ' ' 
			&& sh->cmd_line[x] != '>' && sh->cmd_line[x] != '<' && sh->cmd_line[x] != '|')
		{
			xx = 0;
			while (sh->cmd_line[x] && sh->cmd_line[x] != ' ' 
				&& sh->cmd_line[x] != '>' && sh->cmd_line[x] != '<' && sh->cmd_line[x] != '|')
			{
				if (sh->cmd_line[x] == '"' || sh->cmd_line[x] == '\'')
                {
					xx = 0;
					init = x;
                    x = check_type_quote(sh->cmd_line, x);
					while(init < x)
					{
						sh->temp[counter][xx] = sh->cmd_line[init];
						xx++;
						init++;
					}
                }
				else
				{
					sh->temp[counter][xx] = sh->cmd_line[x];
					x++;
					xx++;
				}
			}
			sh->temp[counter][xx] = '\0';
			counter++;
		}
		else if (sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<' || sh->cmd_line[x] == '|')
		{
			xx = 0;
			init = x;
			while(sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<' || sh->cmd_line[x] == '|')
				x++;
			while(init < x)
			{
				sh->temp[counter][xx] = sh->cmd_line[init];
				xx++;
				init++;
			}
			sh->temp[counter][xx] = '\0';
			counter++;
		}
	}
	return (counter);
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
		if(ft_strlen(str) > 2 && str[x + 1] == '<' && ft_isprint(str[x + 2]))
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
		if(str[x + 1] == '>' && ft_isprint(str[x + 2]))
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
	if(str[*x_o] == '>' || str[*x_o] == '<')
	{
		if(*x_o > 0 && ft_isalnum(str[*x_o - 1]))
			temp[(*x_d)++] = ' ';
		temp[(*x_d)++] = str[(*x_o)++];
		while(str[*x_o] == '>' || str[*x_o] == '<')
			temp[(*x_d)++] = str[(*x_o)++];
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
		if(str[(*x_o)] != 32 && (str[(*x_o) - 1] == 34 || str[(*x_o) - 1] == 39))
		{
			while(str[(*x_o)] && (str[(*x_o)] != 32 || str[(*x_o)] != '>' ||
				 str[(*x_o)] != '<' || str[(*x_o)] != '|'))
				temp[(*x_d)++] = str[(*x_o)++];
		}
	}
	while(str[*x_o] && token_is_valid(str[*x_o]) && *x_o < max)
	{
		if(str[*x_o] == '\n')
        {
            (*x_o)++;
            continue;
        }
		if(str[*x_o] == 34 || str[*x_o] == 39)	
		{
			while(str[*x_o] != 34 && str[*x_o] != 39)
				temp[(*x_d)++] = str[(*x_o)++];
		}
		if(check_if_special_redir(str, *x_o))
			ft_special_agent_redir(str, temp, &x_o[0], &x_d[0]);
		else if(check_if_pipe(str, *x_o) == true)
			ft_call_plumber(str, temp, &x_o[0], &x_d[0]);
		else
			temp[(*x_d)++] = str[(*x_o)++];
	}
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




