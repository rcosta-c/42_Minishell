/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:49 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 11:52:46 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_heredoc(t_sh *sh, int x) 
{
	char *line;
	char *delimiter;

	delimiter = ft_strdup(sh->comands[x].infile);
	free(sh->comands[x].infile);
	sh->comands[x].infile = ft_strdup(".heredoc_temp.txt");
	sh->comands[x].infile_fd = open(sh->comands[x].infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (sh->comands[x].infile_fd < 0) {
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
		write(sh->comands[x].infile_fd, line, strlen(line));
		free(line);
	}
	free(delimiter);
	close(sh->comands[x].infile_fd);
}


