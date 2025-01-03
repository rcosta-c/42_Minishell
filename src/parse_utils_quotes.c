/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:23 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/03 08:11:42 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_quote_d(t_sh *sh, int n)
{
	int		len;
	int		x;
	int		xx;
	char	*dest;

	x = 0;
	xx = 0;
	sh->tokens[n].d_quote = true;
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
	sh->tokens[n].s_quote = true;
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
