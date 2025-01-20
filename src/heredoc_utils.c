/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:49 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/20 21:11:46 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_exit_sigint(t_sh *sh, char *content, char *delimiter, int x)
{
	free(content);
	content = ft_strdup("\n");
	write(sh->comands[x].infile_fd, content, 1);
	free(content);
	close(sh->comands[x].infile_fd);
	free(delimiter);
}

void	heredoc_exit_clean(t_sh *sh, char *delimiter, char *content, int x)
{
	free(delimiter);
	if (content)
	{
		write(sh->comands[x].infile_fd, content, ft_strlen(content));
		free(content);
	}
	close(sh->comands[x].infile_fd);
}

bool	heredoc_break_conditions(char *line, char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("warning: here-document delimited \
			by end-of-file (wanted '", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		return (true);
	}
	if (ft_strlen(line) == ft_strlen(delimiter)
		&& ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
	{
		free(line);
		return (true);
	}
	return (false);
}
