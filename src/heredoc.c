/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:49 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/14 11:00:20 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_heredoc(t_sh *sh, int x) 
{
	char *line;
	char *delimiter;

	delimiter = ft_strdup(sh->comands[x].inheredoc_file);
	free(sh->comands[x].inheredoc_file);
	sh->comands[x].inheredoc_file = ft_strdup(".heredoc_temp.txt");
	sh->comands[x].inheredoc_fd = open(sh->comands[x].inheredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (sh->comands[x].inheredoc_fd < 0) {
		perror("Error opening .heredoc_temp.txt");
		exit(EXIT_FAILURE);
	}
	ft_sigset_fd();
	while (1)
	{
		write(1, ">", 2);
		line = get_next_line(0);
		if (line == NULL)
		{
			free(line);
			break;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break;
		}
		write(sh->comands[x].inheredoc_fd, line, strlen(line));
		free(line);
	}
	free(delimiter);
	close(sh->comands[x].inheredoc_fd);
}


