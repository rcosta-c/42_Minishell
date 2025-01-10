/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:52:28 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:00:10 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	verify_cmdline(t_sh *sh, char *cmdline)
{
	int	x;
	int	len;

	x = 0;
	len = 0;
	while (cmdline[len])
		len++;
	while (cmdline[x] && (cmdline[x] == 32 || cmdline[x] == 9))
	{
		x++;
	}
	if (x == len)
	{
		sh->cmd_line = NULL;
		return (false);
	}
	return (true);
}

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
			return (temp);
		temp++;
		while (str[temp] && (ft_isalnum(str[temp])
				|| str[temp] == 34 || str[temp] == 39
				|| str[temp] == '_' || str[temp] == '-'
				|| str[temp] == '.' || str[temp] == '/'))
			temp = check_dquote_helper(str, temp);
		return (temp);
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
			return (temp);
		temp++;
		while (str[temp] && (ft_isalnum(str[temp])
				|| str[temp] == 34 || str[temp] == 39
				|| str[temp] == '_' || str[temp] == '-'
				|| str[temp] == '.' || str[temp] == '/'))
			temp = check_squote_helper(str, temp);
		return (temp);
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
