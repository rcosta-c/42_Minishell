/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:18:39 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/28 09:00:05 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_copy_name_helper(t_sh *sh, int *x, int n)
{
	int		z;
	char	temp[500];

	z = 0;
	temp[z] = sh->tokens[n].tokens[*x];
	(*x)++;
	z++;
	while (sh->tokens[n].tokens[*x])
	{
		if (ft_isalnum(sh->tokens[n].tokens[*x]) == 0)
			break ;
		temp[z] = sh->tokens[n].tokens[*x];
		(*x)++;
		z++;
	}
	temp[z] = '\0';
	return (ft_strdup(temp));
}

static char	*ft_get_my_pid(t_sh *sh, int *x)
{
	pid_t	pid;

	(void)sh;
	(*x) += 2;
	pid = getpid();
	return (ft_itoa(pid));
}

char	*expand_token_seeker2(t_sh *sh, int *x, int n, char *c)
{
	if ((*x) > 0)
	{
		if (sh->tokens[n].tokens[*x] == '$'
			&& sh->tokens[n].tokens[*x - 1] == 92)
			return (ft_copy_name_helper(sh, x, n));
	}
	if (sh->tokens[n].tokens[*x] == '$' && sh->tokens[n].tokens[*x + 1] == '$')
		return (ft_get_my_pid(sh, x));
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

	(*x)++;
	bx = 0;
	while (sh->tokens[n].tokens[*x]
		&& sh->tokens[n].tokens[*x] != '.'
		&& sh->tokens[n].tokens[*x] != ' '
		&& sh->tokens[n].tokens[*x] != '='
		&& sh->tokens[n].tokens[*x] != '\''
		&& sh->tokens[n].tokens[*x] != '"'
		&& sh->tokens[n].tokens[*x] != '$')
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
