/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:23 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/29 01:10:13 by rcosta-c         ###   ########.fr       */
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
	dest = malloc(len - 1);
	while(sh->tokens[n].tokens[x])
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
	return(dest);
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
	dest = malloc(len + 1);
	while(sh->tokens[n].tokens[x])
	{
		if(sh->tokens[n].tokens[x] == 39)
			x++;
		else
		{
			dest[xx] = sh->tokens[n].tokens[x];
			x++;
			xx++;
		}
	}
	dest[xx] = '\0';
	free(sh->tokens[n].tokens);
	return(dest);
}

/*void	remove_quoted(t_sh *sh)
{
	int	x;

	if(sh->vars.tk_num == 0)
		return;
	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].d_quote)
		{
			sh->tokens[x].tokens = clean_quote_d(sh->tokens[x].tokens);
		}
		if(sh->tokens[x].s_quote)
		{
			sh->tokens[x].tokens = clean_quote_s(sh->tokens[x].tokens);
		}
		x++;
	}
}*/