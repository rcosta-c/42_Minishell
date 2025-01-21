/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:49 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/20 23:51:55 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_init_heredoc(t_sh *sh, int x)
{
	char	*delimiter;
	char	*name;
	char	*number;

	delimiter = ft_strdup(sh->comands[x].infile);
	free(sh->comands[x].infile);
	number = ft_itoa(x);
	name = join_2_str(".heredoc_temp", ".txt", number, 0);
	sh->comands[x].infile = ft_strdup(name);
	sh->comands[x].infile_fd = open(sh->comands[x].infile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (sh->comands[x].infile_fd < 0)
	{
		perror("Error opening .heredoc_temp.txt");
		exit(EXIT_FAILURE);
	}
	free(number);
	free(name);
	return (delimiter);
}

static char	*join_heredoc_content(char *content, char *line)
{
	char	*new_content;

	if (!content)
		return (ft_strjoin(line, "\n"));
	new_content = join_2_str(content, "\n", line, 2);
	return (new_content);
}

char	*read_heredoc_line(void)
{
	char	buffer[BUFFER_SIZE];
	int		i;
	int		bytes;
	char	c;

	i = 0;
	write(1, ">", 2);
	while (i < BUFFER_SIZE - 1)
	{
		bytes = read(STDIN_FILENO, &c, 1);
		if (bytes <= 0 || g_status == 130)
			return (NULL);
		if (c == '\n')
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

void	handle_heredoc(t_sh *sh, int x)
{
	char	*line;
	char	*delimiter;
	char	*content;

	line = NULL;
	content = NULL;
	delimiter = ft_init_heredoc(sh, x);
	ft_sigset_fd();
	while (1)
	{
		line = read_heredoc_line();
		if (g_status == 130)
		{
			free(line);
			heredoc_exit_sigint(sh, content, delimiter, x);
			return ;
		}
		if (heredoc_break_conditions(line, delimiter) == true)
			break ;
		line = expand_heredoc(sh, line);
		content = join_heredoc_content(content, line);
		free(line);
	}
	heredoc_exit_clean(sh, delimiter, content, x);
	ft_sigset();
}

char	*expand_heredoc(t_sh *sh, char *line)
{
	char	*z;
	int		x;
	int		exp_counter;

	exp_counter = 0;
	z = NULL;
	exp_counter = count_heredoc_expands(line);
	if (exp_counter == 0)
		return (line);
	x = 0;
	while (exp_counter > 0)
	{
		z = join_2_str(z, pre_heredoc_expand(line, &x), NULL, 1);
		z = join_2_str(z, expand_heredoc_seeker(sh, line, &x), NULL, 1);
		exp_counter--;
		if (exp_counter == 0)
		{
			z = expand_heredoc_exit(line, &x, z);
			break ;
		}
	}
	free(line);
	return (z);
}
