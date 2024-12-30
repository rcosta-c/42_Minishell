/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:23 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 18:22:38 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_quote_d(t_sh *sh, int n)//char *str)
{
	int		len;
	int		x;
	int		xx;
	char	*dest;

	x = 0;
	xx = 0;
	len = ft_strlen(sh->tokens[n].tokens);
	dest = ft_calloc(sizeof(char), len - 1);
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
	len = ft_strlen(sh->tokens[n].tokens);
	dest = ft_calloc(sizeof(char), len - 1);
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
