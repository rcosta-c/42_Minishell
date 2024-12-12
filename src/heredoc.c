#include "../includes/minishell.h"

void handle_heredoc(t_sh *sh, int x) 
{
	char *line;

	free(sh->comands[x].inheredoc_file);
	sh->comands[x].inheredoc_file = ft_strdup(".heredoc_temp.txt");
	sh->comands[x].inheredoc_fd = open(sh->comands[x].inheredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (sh->comands[x].inheredoc_fd < 0) {
		perror("Error opening .heredoc_temp.txt");
		exit(EXIT_FAILURE);
	}
	//printf("\n\nESTOU AQUI!!!\n\n");
	ft_sigset();
	while (1)
	{
		write(1, ">", 2);
		line = get_next_line(0);
		if (line == NULL)
		{
			free(line);
			break;
		}
		if (ft_strncmp(line, DELIMITER, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break;
		}
		write(sh->comands[x].inheredoc_fd, line, strlen(line));
		free(line);
	}
	close(sh->comands[x].inheredoc_fd);
}

