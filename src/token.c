/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:51:45 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/09 10:30:35 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_special_agent_redir(char *str, char *temp, int *x_o, int *x_d)
{
	if (str[*x_o] == '>' || str[*x_o] == '<')
	{
		if (*x_o > 0 && ft_isalnum(str[*x_o - 1]))
			temp[(*x_d)++] = ' ';
		temp[(*x_d)++] = str[(*x_o)++];
		while (str[*x_o] == '>' || str[*x_o] == '<')
			temp[(*x_d)++] = str[(*x_o)++];
		temp[(*x_d)++] = ' ';
		if (str[*x_o] == 32)
			(*x_o)++;
		return ;
	}
}

static void	ft_call_plumber(char *str, char *temp, int *x_o, int *x_d)
{
	if (str[*x_o] == 32)
		ft_give_some_space(str, temp, &x_o[0], &x_d[0]);
	if (*x_o > 0)
	{
		if (str[*x_o - 1] != ' ')
			temp[(*x_d)++] = ' ';
	}
	temp[(*x_d)++] = str[(*x_o)++];
}

static void	handle_quotes(char *str, char *temp, int *x_o, int *x_d)
{
	if (check_if_dquote(str, *x_o) || check_if_squote(str, *x_o))
	{
		temp[(*x_d)++] = str[(*x_o)++];
		while (str[*x_o] != 34 && str[*x_o] != 39)
			temp[(*x_d)++] = str[(*x_o)++];
	}
	else
		temp[(*x_d)++] = str[(*x_o)++];
	if (str[(*x_o)] != 32 && (str[(*x_o) - 1] == 34 || str[(*x_o) - 1] == 39))
	{
		while (str[(*x_o)] && (str[(*x_o)] != 32 || str[(*x_o)] != '>'
				|| str[(*x_o)] != '<' || str[(*x_o)] != '|'))
			temp[(*x_d)++] = str[(*x_o)++];
	}
}

static int	process_chunk(char *str, char *temp, int *x_o, int *x_d)
{
	int	max;

	max = ft_strlen(str);
	if (str[*x_o] == 32)
		ft_give_some_space(str, temp, &x_o[0], &x_d[0]);
	if (str[*x_o] == 34 || str[*x_o] == 39)
		handle_quotes(str, temp, x_o, x_d);
	while (str[*x_o] && token_is_valid(str[*x_o]) && *x_o < max)
	{
		if (str[*x_o] == '\n')
			(*x_o)++;
		if (str[*x_o] == 34 || str[*x_o] == 39)
			while (str[*x_o] != 34 && str[*x_o] != 39)
				temp[(*x_d)++] = str[(*x_o)++];
		if (check_if_special_redir(str, *x_o))
			ft_special_agent_redir(str, temp, &x_o[0], &x_d[0]);
		else if (check_if_pipe(str, *x_o) == true)
			ft_call_plumber(str, temp, &x_o[0], &x_d[0]);
		else
			temp[(*x_d)++] = str[(*x_o)++];
	}
	if (str[*x_o] == 32)
		ft_give_some_space(str, temp, &x_o[0], &x_d[0]);
	return (*x_o);
}

char	*prepare_line(char *str)
{
	int		x_o[1];
	int		x_d[1];
	char	temp[10000];

	x_o[0] = 0;
	x_d[0] = 0;
	if (ft_strlen(str) == 0)
		return (ft_strdup(""));
	while (str[x_o[0]])
		x_o[0] = process_chunk(str, temp, &x_o[0], &x_d[0]);
	temp[x_d[0]] = '\0';
	free(str);
	return (ft_strdup(temp));
}
