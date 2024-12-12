#include "../includes/minishell.h"

void handle_heredoc(t_sh *sh, int x) 
{
    char *line;
    char *delimiter;

    line = NULL;
    delimiter = sh->comands[x].inheredoc_file;
    printf("\n\n%s\n", sh->comands[x].inheredoc_file);
    sh->comands[x].inheredoc_file = ft_strdup(".heredoc_temp.txt");
    printf("\n\n%s\n", sh->comands[x].inheredoc_file);
    sh->comands[x].inheredoc_fd = open(sh->comands[x].inheredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (sh->comands[x].inheredoc_fd < 0) {
        perror("Error opening .heredoc_temp.txt");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        ft_sigset();
        printf(">");
        line = get_next_line(0); // Lê da entrada padrão (fd 0)
        if (line == NULL)
            break;
        if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
        {
            free(line);
            break;
        }
        write(sh->comands[x].inheredoc_fd, line, strlen(line));
        free(line);
    }
    close(sh->comands[x].inheredoc_fd);
    free(delimiter);   
}




