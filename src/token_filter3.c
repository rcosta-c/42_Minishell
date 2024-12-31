/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 23:28:20 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/31 00:46:15 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	filter_args_checker(t_sh *sh, int n)
{
	if (sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false
		&& sh->tokens[n].r_in == false
		&& sh->tokens[n].r_out == false
		&& sh->tokens[n].r_heredoc == false
		&& sh->tokens[n].r_outappend == false
		&& sh->tokens[n].pipe == false
		&& sh->tokens[n].file == false
		&& sh->tokens[n].exp_e == false
		&& sh->tokens[n].f_quote == false
		&& sh->tokens[n].exp_t == false
		&& sh->tokens[n].r_outappend == false)
	{
		sh->tokens[n].arg = true;
	}
}

int	filter_envp_helper(t_sh *sh, int n, int x)
{
	x++;
	if (ft_isalnum(sh->tokens[n].tokens[x]) != 0
		|| sh->tokens[n].tokens[x] == '$'
		|| sh->tokens[n].tokens[x] == '?')
		sh->tokens[n].exp_e = true;
	while ((sh->tokens[n].tokens[x] >= 'A'
			&& sh->tokens[n].tokens[x] <= 'Z')
		|| sh->tokens[n].tokens[x] == '$'
		|| sh->tokens[n].tokens[x] == '?')
		x++;
	return (x);
}

void	filter_quotes_helper(t_sh *sh, int n, int counter_s, int counter_d)
{
	if (counter_s == 2)
	{
		sh->tokens[n].s_quote = true;
		sh->tokens[n].tokens = clean_quote_s(sh, n);
	}
	else if (counter_d == 2)
	{
		sh->tokens[n].d_quote = true;
		sh->tokens[n].tokens = clean_quote_d(sh, n);
	}
	else if (counter_d == 0)
		sh->tokens[n].d_quote = false;
	else if (counter_s == 0)
		sh->tokens[n].s_quote = false;
	else if (counter_d == 1 || counter_s == 1)
		sh->tokens[n].f_quote = true;
}

char	*pre_expand(t_sh *sh, int *x, int n)
{
	int		xa;
	char	*a;

	xa = 0;
	while (sh->tokens[n].tokens[*x + xa]
		&& sh->tokens[n].tokens[*x + xa] != '$'
		&& sh->tokens[n].tokens[*x + xa] != '~')
		xa++;
	a = malloc(sizeof(char) * (xa + 1));
	if (!a)
		return (NULL);
	xa = 0;
	while (sh->tokens[n].tokens[*x]
		&& sh->tokens[n].tokens[*x] != '$'
		&& sh->tokens[n].tokens[*x] != '~')
	{
		a[xa] = sh->tokens[n].tokens[*x];
		(*x)++;
		xa++;
	}
	a[xa] = '\0';
	return (a);
}