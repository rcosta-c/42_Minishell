/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:52:56 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/06 13:01:30 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_if_dquote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	if (str[x_o] != 34)
		return (false);
	while (str[x])
	{
		if (str[x] == 34)
			counter++;
		x++;
	}
	if (counter % 2 != 0)
		return (true);
	else
		return (false);
}

bool	check_if_squote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	if (str[x_o] != 39)
		return (false);
	while (str[x])
	{
		if (str[x] == 39)
			counter++;
		x++;
	}
	if (counter % 2 != 0)
		return (true);
	else
		return (false);
}

bool	search_ext(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == '.')
			return (true);
		len--;
	}
	return (false);
}

static void	re_init_tokens(t_sh *sh, int n_tk_num, char n_temp[50][50])
{
	int	counter;
	int	xx;

	free_tokens(sh);
	sh->vars.tk_num = sh->vars.tk_num - n_tk_num;
	counter = 0;
	while (counter < 50)
	{
		xx = -1;
		while (n_temp[counter][++xx])
			sh->temp[counter][xx] = n_temp[counter][xx];
		sh->temp[counter][xx] = '\0';
		counter++;
	}
	sh->vars.cmds_num = 0;
	sh->vars.pipe_num = 0;
	sh->vars.redir_tot = 0;
	sh->vars.heredoc_num = 0;
	init_tokens(sh);
	filter_tokens(sh);
}

void	check_invalid_start(t_sh *sh)
{
	int		x;
	int		xx;
	int		counter;
	char	n_temp[50][50];
	int		n_tk_num;

	n_tk_num = 0;
	x = 0;
	counter = init_check_invalid_start(sh, n_temp);
	if (counter == 0)
		return ;
	else
	{
		n_tk_num = counter;
		x = 0;
		while (counter < sh->vars.tk_num)
		{
			xx = -1;
			while (sh->tokens[counter].tokens[++xx])
				n_temp[x][xx] = sh->tokens[counter].tokens[xx];
			x++;
			counter++;
		}
		re_init_tokens(sh, n_tk_num, n_temp);
	}
}
