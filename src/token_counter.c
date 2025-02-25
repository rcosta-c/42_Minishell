/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:17:25 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/08 15:04:51 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_quote_token(t_sh *sh, int x)
{
	x = check_type_quote(sh->cmd_line, x);
	sh->vars.tk_num++;
	return (x);
}

static int	counter_regular_token(t_sh *sh, int x)
{
	while (sh->cmd_line[x] && sh->cmd_line[x] != ' '
		&& sh->cmd_line[x] != '>'
		&& sh->cmd_line[x] != '<'
		&& sh->cmd_line[x] != '|')
	{
		if (sh->cmd_line[x] == 39 || sh->cmd_line[x] == 34)
		{
			x = check_type_quote(sh->cmd_line, x);
		}
		else
			x++;
	}
	return (x);
}

static int	count_special_token(t_sh *sh, int x)
{
	while (sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<'
		|| sh->cmd_line[x] == '|')
		x++;
	sh->vars.tk_num++;
	return (x);
}

void	count_tokens(t_sh *sh)
{
	int	x;

	x = 0;
	while (sh->cmd_line[x])
	{
		while (sh->cmd_line[x] == ' ')
			x++;
		if (sh->cmd_line[x] == 34 || sh->cmd_line[x] == 39)
			x = count_quote_token(sh, x);
		else if (sh->cmd_line[x] && sh->cmd_line[x] != ' '
			&& sh->cmd_line[x] != '>'
			&& sh->cmd_line[x] != '<'
			&& sh->cmd_line[x] != '|')
		{
			x = counter_regular_token(sh, x);
			sh->vars.tk_num++;
		}
		else if (sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<'
			|| sh->cmd_line[x] == '|')
			x = count_special_token(sh, x);
	}
	return ;
}

bool	counter_validation(int c)
{
	if (c == 33 || (c >= 35 && c <= 38) || (c >= 40 && c <= 176))
		return (true);
	else
		return (false);
}
