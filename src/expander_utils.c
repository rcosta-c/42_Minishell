/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:09 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/31 00:39:06 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_exit(t_sh *sh, int n, int x, char *z)
{
	int		xa;
	char	a[5000];

	xa = 0;
	while (sh->tokens[n].tokens[x])
		a[xa++] = sh->tokens[n].tokens[x++];
	a[xa] = '\0';
	return (join_2_str(z, a, NULL, 2));
}

int	ft_envp_n_cmp(const char *s1, const char *s2)
{
	size_t	counter;
	size_t	n;

	n = ft_strlen(s1);
	counter = 0;
	if (n == 0)
		return (0);
	while (s1[counter] == s2[counter] && s1[counter] != '\0')
	{
		if (counter < (n - 1))
			counter++;
		else
			return (0);
	}
	if (s2[counter] == '=')
		return ((unsigned char)(s1[counter]) - (unsigned char)(s2[counter]));
	else
		return ((unsigned char)(s2[counter]));
}

char	*search_envp(t_sh *sh, char *z)
{
	int		x;
	int		xx;
	int		xt;
	char	temp[5000];

	xx = 0;
	x = 0;
	xt = 0;
	while (sh->envp[x])
	{
		if (ft_envp_n_cmp(z, sh->envp[x]) == 0)
		{
			while (sh->envp[x][xx] != '=')
				xx++;
			xx++;
			while (sh->envp[x][xx])
				temp[xt++] = sh->envp[x][xx++];
			temp[xt] = '\0';
			return (ft_strdup(temp));
		}
		else
			x++;
	}
	return (NULL);
}

int	count_expands(t_sh *sh, int n)
{
	int	x;
	int	exp_counter;

	exp_counter = 0;
	x = 0;
	while (sh->tokens[n].tokens[x])
	{
		if (sh->tokens[n].tokens[x] == '$')
			exp_counter++;
		else if (sh->tokens[n].tokens[x] == '~'
			&& sh->tokens[n].d_quote == false
			&& sh->tokens[n].s_quote == false)
			exp_counter++;
		else if (sh->tokens[n].tokens[x] == '$'
			&& (sh->tokens[n].tokens[x + 1] == '$'
				|| sh->tokens[n].tokens[x + 1] == '?'))
			exp_counter++;
		x++;
	}
	return (exp_counter);
}

void	expand_exit_token(t_sh *sh, int *x, int n, char *c)
{
	(void)c;
	if (sh->tokens[n].tokens[*x] == '$'
		&& sh->tokens[n].tokens[*x + 1] == '?')
	{
		(*x)++;
		c = ft_itoa(g_status);
		(*x)++;
	}
}
