/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:12:22 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 22:44:53 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_if_special_redirin(char *str, int x)
{
	if (str[x] == '<')
	{
		if (ft_strlen(str) > 2 && str[x + 1] == '<' && ft_isprint(str[x + 2]))
			return (true);
		else if (str[x + 1] && ft_isprint(str[x + 1]))
			return (true);
		else
			return (false);
	}
	return (false);
}

bool	check_if_special_redirout(char *str, int x)
{
	if (str[x] == '>')
	{
		if (str[x + 1] == '>' && ft_isprint(str[x + 2]))
			return (true);
		else if (str[x + 1] && ft_isprint(str[x + 1]))
			return (true);
		else
			return (false);
	}
	return (false);
}

bool	check_if_special_redir(char *str, int x)
{
	if (check_if_special_redirin(str, x) == true)
		return (true);
	else if (check_if_special_redirout(str, x) == true)
		return (true);
	else
		return (false);
}

void	ft_give_some_space(char *str, char *temp, int *x_o, int *x_d)
{
	while (str[*x_o] == 32)
		(*x_o)++;
	if (str[*x_o] != '\0' && *x_d > 0)
		temp[(*x_d)++] = 32;
}

bool	check_if_pipe(char *str, int x_o)
{
	if (str[x_o] == '|')
		return (true);
	else
		return (false);
}
