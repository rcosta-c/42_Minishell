/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:52:56 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/08 23:36:16 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_if_dquote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	if (str[x_o] != 34)
		return (false);
	while (str[x])
	{
		if (str[x] == 34)
			counter++;
		x++;
	}
	if (counter % 2 != 0)
		return (true);
	else
		return (false);
}

bool	check_if_squote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	if (str[x_o] != 39)
		return (false);
	while (str[x])
	{
		if (str[x] == 39)
			counter++;
		x++;
	}
	if (counter % 2 != 0)
		return (true);
	else
		return (false);
}

bool	search_ext(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == '.')
			return (true);
		len--;
	}
	return (false);
}

void	check_invalid_start(t_sh *sh)
{
	int		counter;

	counter = init_check_invalid_start(sh);
	if (counter == 0)
		return ;
	else if ((counter >= 1))
	{
		free(sh->tokens[0].tokens);
		sh->tokens[0].pipe = true;
		sh->tokens[0].tokens = ft_strdup("|");
	}
}
