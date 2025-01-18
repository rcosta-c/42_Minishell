/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:28:50 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/14 12:48:22 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*exph3_helper(t_sh *sh, char *line, int *x, char *b)
{
	int		bx;
	char	*c;

	bx = 0;
	(*x)++;
	while (line[*x]
		&& line[*x] != ' '
		&& line[*x] != '='
		&& line[*x] != '\'')
	{
		b[bx++] = line[(*x)++];
	}
	b[bx] = '\0';
	c = search_envp(sh, b);
	if (!c)
	{
		c = ft_strdup(" ");
	}
	return (c);
}

static bool	exphrdc3_hlp(bool in_quotes)
{
	if (in_quotes == true)
		return (false);
	else
		return (true);
}

char	*expand_heredoc_seeker3(t_sh *sh, char *line, int *x)
{
	char	b[2500];
	bool	in_quotes;
	char	*c;

	c = NULL;
	in_quotes = false;
	while (line[*x])
	{
		if (line[*x] == '\'')
		{
			in_quotes = exphrdc3_hlp(in_quotes);
			(*x)++;
			continue ;
		}
		if (in_quotes == false && line[*x] == '$')
		{
			c = exph3_helper(sh, line, x, b);
			break ;
		}
		else
			(*x)++;
	}
	return (c);
}
