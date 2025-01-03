/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:46:16 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/03 08:18:30 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_redirection_token(t_sh *sh, int x)
{
	if (sh->tokens[x].r_in == true || sh->tokens[x].r_heredoc == true || \
			sh->tokens[x].r_outappend == true || sh->tokens[x].r_out == true)
		return (true);
	else
		return (false);
}

static int	process_quotes(t_sh *sh, int x)
{
	int	counter;

	counter = 0;
	if (sh->tokens[x].d_quote == true || sh->tokens[x].s_quote == true)
	{
		x++;
		counter++;
	}
	while (x < sh->vars.tk_num && (sh->tokens[x].d_quote == true
			|| sh->tokens[x].s_quote == true))
	{
		sh->tokens[x].arg = false;
		sh->tokens[x].d_quote = false;
		sh->tokens[x].s_quote = false;
		x++;
		counter++;
	}
	return (counter);
}

static void	join_quote_tokens(t_sh *sh, int x, int counter)
{
	int		xx;
	char	*temp;

	xx = 0;
	while (xx < counter)
	{
		temp = ft_strjoin(sh->tokens[x - xx - 1].tokens,
				sh->tokens[x - xx].tokens);
		free(sh->tokens[x - xx - 1].tokens);
		sh->tokens[x - xx - 1].tokens = ft_strdup(temp);
		free(temp);
		xx++;
	}
}

void	ft_redir_multiargs(t_sh *sh)
{
	int	x;
	int	counter;

	x = 0;
	if (sh->vars.redir_tot == 0 || sh->vars.tk_num < 4)
		return ;
	while (x < sh->vars.tk_num)
	{
		if (x > 0 && is_redirection_token(sh, x))
		{
			if (x >= sh->vars.tk_num)
				break ;
			if (sh->tokens[x].tokens[0] == 34 || sh->tokens[x].tokens[0] == 39)
			{
				counter = process_quotes(sh, x);
				if (counter > 1)
				{
					join_quote_tokens(sh, x, counter);
					x += counter - 1;
				}
			}
		}
		x++;
	}
}
