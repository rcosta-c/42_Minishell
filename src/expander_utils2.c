/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:18:39 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/18 11:25:32 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_token_seeker2(t_sh *sh, int *x, int n, char *c)
{
	pid_t	pid;

	if (sh->tokens[n].tokens[*x] == '$' && sh->tokens[n].tokens[*x + 1] == '$')
	{
		(*x) += 2;
		pid = getpid();
		return (ft_itoa(pid));
	}
	if (sh->tokens[n].tokens[*x] == '$' && sh->tokens[n].tokens[*x + 1] == '?')
	{
		(*x) += 2;
		return (ft_itoa(g_status));
	}
	if (sh->tokens[n].tokens[*x] == '$'
		&& (sh->tokens[n].tokens[*x + 1] == '\0'
			|| !ft_isalpha(sh->tokens[n].tokens[*x + 1])))
	{
		(*x)++;
		return (ft_strdup("$"));
	}
	if (sh->tokens[n].tokens[*x] == '$')
		return (expand_token_seeker3(sh, n, x));
	return (c);
}

char	*expand_token_seeker3(t_sh *sh, int n, int *x)
{
	char	b[2500];
	int		bx;
	char	*c;

	if (sh->tokens[n].s_quote)
		return (NULL);
	(*x)++;
	bx = 0;
	while (sh->tokens[n].tokens[*x]
		&& sh->tokens[n].tokens[*x] != ' '
		&& sh->tokens[n].tokens[*x] != '='
		&& sh->tokens[n].tokens[*x] != '\''
		&& sh->tokens[n].tokens[*x] != '"')
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
