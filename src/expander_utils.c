/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:09 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/18 11:39:58 by rcosta-c         ###   ########.fr       */
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

	if (ft_strlen(s2) > ft_strlen(s1))
		n = ft_strlen(s2);
	else
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
	if (s1[counter] == '\0' && s2[counter] == '=')
		return (0);
	else if (s2[counter] == '=')
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

int	count_expands(t_sh *sh, int n, int exp_counter)
{
	int		x;
	bool	in_single_quotes;

	x = 0;
	in_single_quotes = false;
	while (sh->tokens[n].tokens[x])
	{
		if (sh->tokens[n].tokens[x] == '\'' && !sh->tokens[n].d_quote)
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && !sh->tokens[n].s_quote)
		{
			if (sh->tokens[n].tokens[x] == '$')
			{
				if (sh->tokens[n].tokens[x + 1] == '$'
					|| sh->tokens[n].tokens[x + 1] == '?')
					x++;
				exp_counter++;
			}
			else if (sh->tokens[n].tokens[x] == '~'
				&& !sh->tokens[n].d_quote)
				exp_counter++;
		}
		x++;
	}
	return (exp_counter);
}

int	prep_search(t_sh *sh, int n, int x)
{
	while (sh->tokens[n].tokens[x++])
	{
		if (sh->tokens[n].tokens[x] == '$')
			expand_token(sh, n);
	}
	return (x);
}
