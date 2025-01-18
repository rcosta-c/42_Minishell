/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:03 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/14 12:49:56 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expand_heredoc_seeker2(t_sh *sh, char *line, int *x, char *c)
{
	if (line[*x] == '$'
		&& line[*x + 1] == '?')
	{
		(*x)++;
		c = ft_itoa(g_status);
		(*x)++;
	}
	if (line[*x] == '$'
		&& (line[*x + 1] == '\0' || ft_isalpha(line[*x + 1]) == 0))
		return (ft_strdup("$"));
	else if (line[*x] == '$')
		c = expand_heredoc_seeker3(sh, line, x);
	return (c);
}

char	*expand_heredoc_seeker(t_sh *sh, char *line, int *x)
{
	char	*c;
	pid_t	pid;

	c = NULL;
	if (line[*x] == '~'
		&& line[*x + 1] == '/')
	{
		c = search_envp(sh, "HOME");
		(*x)++;
	}
	else if (line[*x] == '$'
		&& line[*x + 1] == '$')
	{
		(*x)++;
		pid = getpid();
		c = ft_itoa(pid);
		(*x)++;
	}
	else
		return (expand_heredoc_seeker2(sh, line, x, c));
	return (c);
}

int	count_heredoc_expands(char *line)
{
	int	x;
	int	exp_counter;

	exp_counter = 0;
	x = 0;
	while (line[x])
	{
		if (line[x] == '$')
			exp_counter++;
		else if (line[x] == '~' && line[x + 1] == '/')
			exp_counter++;
		else if (line[x] == '$' && (line[x + 1] == '$'
				|| line[x + 1] == '?'))
			exp_counter++;
		x++;
	}
	return (exp_counter);
}

char	*pre_heredoc_expand(char *line, int *x)
{
	int		xa;
	char	*a;

	xa = 0;
	while (line[*x + xa] && line[*x + xa] != '$')
	{
		if (line[*x + xa] == '~' && line[*x + xa] == '/')
			break ;
		xa++;
	}
	a = malloc(sizeof(char) * (xa + 1));
	if (!a)
		return (NULL);
	xa = 0;
	while (line[*x] && line[*x] != '$')
	{
		if (line[*x + xa] && line[*x + xa] == '~' && line[*x + xa] == '/')
			break ;
		a[xa] = line[*x];
		(*x)++;
		xa++;
	}
	a[xa] = '\0';
	return (a);
}

char	*expand_heredoc_exit(char *line, int *x, char *z)
{
	int		xa;
	char	a[5000];

	xa = 0;
	while (line[*x])
		a[xa++] = line[(*x)++];
	a[xa] = '\0';
	return (join_2_str(z, a, NULL, 2));
}
