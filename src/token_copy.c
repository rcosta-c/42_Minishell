/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:17:25 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/08 14:57:49 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	copy_quote_token(t_sh *sh, int x, int *counter)
{
	int		xx;
	int		init;
	char	temp[5000];

	xx = 0;
	init = x;
	x = check_type_quote(sh->cmd_line, x);
	if (x == init)
		temp[xx++] = sh->cmd_line[x++];
	else
	{
		while (init < x)
		{
			temp[xx] = sh->cmd_line[init];
			xx++;
			init++;
		}
	}
	temp[xx] = '\0';
	sh->tokens[(*counter)].tokens = ft_strdup(temp);
	(*counter)++;
	return (x);
}

static int	copy_regular_token(t_sh *sh, int x, int *counter)
{
	int		xx;
	int		init;
	char	temp[5000];

	xx = 0;
	while (sh->cmd_line[x] && sh->cmd_line[x] != ' '
		&& sh->cmd_line[x] != '>'
		&& sh->cmd_line[x] != '<'
		&& sh->cmd_line[x] != '|')
	{
		if (sh->cmd_line[x] == 39 || sh->cmd_line[x] == 34)
		{
			init = x;
			x = check_type_quote(sh->cmd_line, x);
			while (init < x)
				temp[xx++] = sh->cmd_line[init++];
		}
		else
			temp[xx++] = sh->cmd_line[x++];
	}
	temp[xx] = '\0';
	sh->tokens[(*counter)].tokens = ft_strdup(temp);
	(*counter)++;
	return (x);
}

static int	copy_special_token(t_sh *sh, int x, int *counter)
{
	int		xx;
	int		init;
	char	temp[5000];

	xx = 0;
	init = x;
	while (sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<'
		|| sh->cmd_line[x] == '|')
		x++;
	while (init < x)
	{
		temp[xx] = sh->cmd_line[init];
		xx++;
		init++;
	}
	temp[xx] = '\0';
	sh->tokens[*counter].tokens = ft_strdup(temp);
	(*counter)++;
	return (x);
}

void	copy_tokens(t_sh *sh)
{
	int	x;
	int	counter;

	x = 0;
	counter = 0;
	while (counter < sh->vars.tk_num)
	{
		while (sh->cmd_line[x] == ' ')
			x++;
		if (sh->cmd_line[x] == 34 || sh->cmd_line[x] == 39)
			x = copy_quote_token(sh, x, &counter);
		else if (sh->cmd_line[x] && sh->cmd_line[x] != ' '
			&& sh->cmd_line[x] != '>'
			&& sh->cmd_line[x] != '<'
			&& sh->cmd_line[x] != '|')
			x = copy_regular_token(sh, x, &counter);
		else if (sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<'
			|| sh->cmd_line[x] == '|')
			x = copy_special_token(sh, x, &counter);
	}
	return ;
}
