/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:52:28 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/01 23:57:01 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	token_is_valid(char src)
{
	if (src == 10 || src == 33 || (src >= 35 && src <= 126))
		return (true);
	else if (src == 9)
		return (true);
	else
		return (false);
}

int	check_dquote(char *str, int counter)
{
	int	temp;

	temp = counter;
	if (str[temp] == 34)
	{
		temp++;
		while (str[temp] && str[temp] != 34)
			temp++;
		if (str[temp] == '\0')
			return (counter);
		else if (str[temp] == 34 && ft_isalnum(str[temp + 1]))
		{
			temp++;
			while (str[temp] && ft_isalnum(str[temp]))
				temp++;
			return (temp);
		}
		else
		{
			temp++;
			return (temp);
		}
	}
	return (counter);
}

int	check_squote(char *str, int counter)
{
	int	temp;

	temp = counter;
	if (str[temp] == 39)
	{
		temp++;
		while (str[temp] && str[temp] != 39)
			temp++;
		if (str[temp] == '\0')
			return (counter);
		else if (str[temp] == 39 && ft_isalnum(str[temp + 1]))
		{
			temp++;
			while (str[temp] && ft_isalnum(str[temp]))
				temp++;
			return (temp);
		}
		else
		{
			temp++;
			return (temp);
		}
	}
	return (counter);
}

int	check_type_quote(char *cmd_line, int x)
{
	if (cmd_line[x] == 34)
	{
		return (check_dquote(cmd_line, x));
	}
	else if (cmd_line[x] == 39)
	{
		return (check_squote(cmd_line, x));
	}
	else
		return (x);
}
