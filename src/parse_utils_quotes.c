/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:23 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/18 11:13:39 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleaning_quotes(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.tk_num)
	{
		if (sh->tokens[x].d_quote == true)
			sh->tokens[x].tokens = clean_quote_d(sh, x);
		if (sh->tokens[x].s_quote == true)
			sh->tokens[x].tokens = clean_quote_s(sh, x);
		x++;
	}
}

char	*clean_quote_d(t_sh *sh, int n)
{
	int		len;
	int		x;
	int		xx;
	char	*dest;

	x = 0;
	xx = 0;
	if (n == 0 && ft_strlen(sh->tokens[n].tokens) == 2)
		return (sh->tokens[n].tokens);
	len = ft_strlen(sh->tokens[n].tokens);
	dest = ft_calloc(sizeof(char), len + 1);
	while (sh->tokens[n].tokens[x])
	{
		if (sh->tokens[n].tokens[x] != 34)
		{
			dest[xx] = sh->tokens[n].tokens[x];
			xx++;
		}
		x++;
	}
	dest[xx] = '\0';
	free(sh->tokens[n].tokens);
	return (dest);
}

char	*clean_quote_s(t_sh *sh, int n)
{
	int		len;
	int		x;
	int		xx;
	char	*dest;

	x = 0;
	xx = 0;
	if (n == 0 && ft_strlen(sh->tokens[n].tokens) == 2)
		return (sh->tokens[n].tokens);
	len = ft_strlen(sh->tokens[n].tokens);
	dest = ft_calloc(sizeof(char), len + 1);
	while (sh->tokens[n].tokens[x])
	{
		if (sh->tokens[n].tokens[x] != 39)
		{
			dest[xx] = sh->tokens[n].tokens[x];
			xx++;
		}
		x++;
	}
	dest[xx] = '\0';
	free(sh->tokens[n].tokens);
	return (dest);
}
