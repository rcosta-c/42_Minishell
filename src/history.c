/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:15:39 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 13:51:05 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_history_entries(t_sh *sh)
{
	char	*line;
	int		fd;
	int		x;
	char	*dir;

	x = 0;
	dir = ft_strjoin(sh->vars.minihome, "/.history");
	fd = open(dir, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening history file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		x++;
		free(line);
	}
	close(fd);
	free(dir);
	x++;
	return (x);
}

void	save_to_history(t_sh *sh, char *cmd_line)
{
	int		fd;
	char	*entry_number;
	char	*dir;

	add_history(cmd_line);
	entry_number = ft_itoa(count_history_entries(sh));
	dir = ft_strjoin(sh->vars.minihome, "/.history");
	fd = open(dir, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error opening history file");
		return ;
	}
	if (write(fd, entry_number, ft_strlen(entry_number)) == -1
		|| write(fd, cmd_line, ft_strlen(cmd_line)) == -1
		|| write(fd, "\n", 1) == -1)
	{
		perror("Error writing history file");
	}
	close(fd);
	free(dir);
	free(entry_number);
	return ;
}
