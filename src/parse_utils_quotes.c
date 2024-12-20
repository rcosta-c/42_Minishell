/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:23 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/20 00:09:34 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*clean_quote(char *str)
{
	int		len;
	int		x;
	int		xx;
	char	*dest;

	x = 0;
	xx = 0;
	len = ft_strlen(str);
	dest = malloc(sizeof(char *) * len - 1);
	while(str[x])
	{
		if(str[x] == 34)
			x++;
		else
		{
			dest[xx] = str[x];
			x++;
			xx++;
		}
	}
	dest[xx] = '\0';
	free(str);
	return(dest);
}

void	remove_quoted(t_sh *sh)
{
	int	x;

	if(sh->vars.tk_num == 0)
		return;
	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].d_quote)
		{
			sh->tokens[x].tokens = clean_quote(sh->tokens[x].tokens);
		}
		if(sh->tokens[x].s_quote)
		{
			sh->tokens[x].tokens = clean_quote(sh->tokens[x].tokens);
		}
		x++;
	}
}