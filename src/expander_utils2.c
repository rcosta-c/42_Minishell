/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:18:39 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:46:37 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expt3_helper(t_sh *sh, int n, int *x, char *b)
{
	int		bx;
	char	*c;

	bx = 0;
	(*x)++;
	while (sh->tokens[n].tokens[*x]
		&& sh->tokens[n].tokens[*x] != ' '
		&& sh->tokens[n].tokens[*x] != '='
		&& sh->tokens[n].tokens[*x] != '\'')
	{
		b[bx++] = sh->tokens[n].tokens[(*x)++];
	}
	b[bx] = '\0';
	c = search_envp(sh, b);
	if (!c)
	{
		c = ft_strdup(" ");
		sh->tokens[n].exp_empty = true;
	}
	return (c);
}

static bool	exptksk3_hlp(bool in_quotes)
{
	if (in_quotes == true)
		return (false);
	else
		return (true);
}

char	*expand_token_seeker3(t_sh *sh, int n, int *x)
{
	char	b[2500];
	bool	in_quotes;
	char	*c;

	c = NULL;
	in_quotes = false;
	while (sh->tokens[n].tokens[*x])
	{
		if (sh->tokens[n].tokens[*x] == '\'')
		{
			in_quotes = exptksk3_hlp(in_quotes);
			(*x)++;
			continue ;
		}
		if (in_quotes == false && sh->tokens[n].tokens[*x] == '$')
		{
			c = expt3_helper(sh, n, x, b);
			break ;
		}
		else
			(*x)++;
	}
	return (c);
}
