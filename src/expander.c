/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:03 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/20 23:17:45 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_expand(t_sh *sh)
{
	int	x;
	int	n;

	n = 0;
	x = 0;
	while (n < sh->vars.tk_num)
	{
		if (!sh->tokens[n].tokens)
			(void)n;
		else if (sh->tokens[n].tokens[0] == '$'
			&& ft_strlen(sh->tokens[n].tokens) == 1)
			ft_strlen(sh->tokens[n].tokens);
		else if (sh->tokens[n].exp_e || sh->tokens[n].exp_t)
			expand_token(sh, n);
		else if (sh->tokens[n].d_quote
			&& (sh->tokens[n].exp_e || sh->tokens[n].exp_t))
			x = prep_search(sh, n, x);
		else if (sh->tokens[n].file && sh->tokens[n].exp_t
			&& sh->tokens[n].exp_e)
		{
			expand_token(sh, n);
		}
		n++;
	}
}

void	expand_token(t_sh *sh, int n)
{
	char	*z;
	int		x;
	int		exp_counter;

	exp_counter = 0;
	z = NULL;
	exp_counter = count_expands(sh, n, exp_counter);
	x = 0;
	if (exp_counter == 0)
		return ;
	while (exp_counter > 0)
	{
		z = join_2_str(z, pre_expand(sh, &x, n), NULL, 1);
		z = join_2_str(z, expand_token_seeker(sh, &x, n), NULL, 1);
		exp_counter--;
		if (exp_counter == 0)
		{
			z = expand_exit(sh, n, x, z);
			break ;
		}
	}
	free(sh->tokens[n].tokens);
	sh->tokens[n].tokens = z;
}

static int	pre_expand_helper(t_sh *sh, int *x, int n)
{
	int		xa;
	bool	in_single_quotes;

	xa = 0;
	in_single_quotes = false;
	while (sh->tokens[n].tokens[*x + xa])
	{
		if (sh->tokens[n].tokens[*x + xa] == '\'' && !sh->tokens[n].d_quote)
			in_single_quotes = !in_single_quotes;
		if (!in_single_quotes && !sh->tokens[n].s_quote
			&& (sh->tokens[n].tokens[*x + xa] == '$'
				|| (sh->tokens[n].tokens[*x + xa] == '~'
					&& !sh->tokens[n].d_quote)))
			break ;
		xa++;
	}
	return (xa);
}

char	*pre_expand(t_sh *sh, int *x, int n)
{
	int		xa;
	char	*a;
	bool	in_single_quotes;

	xa = pre_expand_helper(sh, x, n);
	a = malloc(sizeof(char) * (xa + 1));
	xa = 0;
	in_single_quotes = false;
	while (sh->tokens[n].tokens[*x])
	{
		if (sh->tokens[n].tokens[*x] == '\'' && !sh->tokens[n].d_quote)
		{
			in_single_quotes = !in_single_quotes;
			a[xa++] = sh->tokens[n].tokens[(*x)++];
			continue ;
		}
		if (!in_single_quotes && (sh->tokens[n].tokens[*x] == '$'
				|| (sh->tokens[n].tokens[*x] == '~'
					&& !sh->tokens[n].d_quote)))
			break ;
		a[xa++] = sh->tokens[n].tokens[(*x)++];
	}
	a[xa] = '\0';
	return (a);
}

char	*expand_token_seeker(t_sh *sh, int *x, int n)
{
	char	c[1024];
	int		xx;

	xx = 0;
	if (sh->tokens[n].tokens[*x] == '\'' && !sh->tokens[n].d_quote)
	{
		(*x)++;
		while (sh->tokens[n].tokens[*x] && sh->tokens[n].tokens[*x] != '\'')
		{
			c[xx++] = sh->tokens[n].tokens[(*x)++];
		}
		c[xx] = '\0';
		if (sh->tokens[n].tokens[*x] == '\'')
			(*x)++;
		return (ft_strdup(c));
	}
	if (sh->tokens[n].tokens[*x] == '~' && !sh->tokens[n].d_quote)
	{
		(*x)++;
		return (search_envp(sh, "HOME"));
	}
	if (sh->tokens[n].tokens[*x] == '$')
		return (expand_token_seeker2(sh, x, n, c));
	return (NULL);
}
