/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:17:25 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/06 13:01:58 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_quote_token(t_sh *sh, int x, int counter)
{
	int	xx;
	int	init;

	xx = 0;
	init = x;
	x = check_type_quote(sh->cmd_line, x);
	if (x == init)
		sh->temp[counter][xx++] = sh->cmd_line[x++];
	else
	{
		while (init < x)
		{
			sh->temp[counter][xx] = sh->cmd_line[init];
			xx++;
			init++;
		}
	}
	sh->temp[counter][xx] = '\0';
	sh->vars.tk_num++;
	return (x);
}

static int	counter_regular_token(t_sh *sh, int x, int counter)
{
	int	xx;
	int	init;

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
				sh->temp[counter][xx++] = sh->cmd_line[init++];
		}
		else
			sh->temp[counter][xx++] = sh->cmd_line[x++];
	}
	sh->temp[counter][xx] = '\0';
	return (x);
}

static int	count_special_token(t_sh *sh, int x, int counter)
{
	int	xx;
	int	init;

	xx = 0;
	init = x;
	while (sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<'
		|| sh->cmd_line[x] == '|')
		x++;
	while (init < x)
	{
		sh->temp[counter][xx] = sh->cmd_line[init];
		xx++;
		init++;
	}
	sh->temp[counter][xx] = '\0';
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
			x = count_quote_token(sh, x, sh->vars.tk_num);
		else if (sh->cmd_line[x] && sh->cmd_line[x] != ' '
			&& sh->cmd_line[x] != '>'
			&& sh->cmd_line[x] != '<'
			&& sh->cmd_line[x] != '|')
		{
			x = counter_regular_token(sh, x, sh->vars.tk_num);
			sh->vars.tk_num++;
		}
		else if (sh->cmd_line[x] == '>' || sh->cmd_line[x] == '<'
			|| sh->cmd_line[x] == '|')
			x = count_special_token(sh, x, sh->vars.tk_num);
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
