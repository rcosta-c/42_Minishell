#include "../includes/minishell.h"

char *handle_nextline_heredoc(int fd) 
{
    static char buffer[BUFFER_SIZE];
    static int bytes_read = 0;
    static int index = 0;
    char *line = NULL;
    int line_length = 0;

    while (1) 
    {
        if (index >= bytes_read) 
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            index = 0;
            if (bytes_read <= 0) 
            {
                if (line_length > 0) 
                {
                    line = realloc(line, line_length + 1);
                    line[line_length] = '\0';
                    return line;
                }
                return NULL; // EOF or error
            }
        }

        // Search for newline
        while (index < bytes_read && buffer[index] != '\n') 
        {
            line = realloc(line, line_length + 1);
            line[line_length++] = buffer[index++];
        }

        // Add newline if found
        if (index < bytes_read && buffer[index] == '\n') 
        {
            line = realloc(line, line_length + 1);
            line[line_length++] = '\n';
            index++;
            line = realloc(line, line_length + 1);
            line[line_length] = '\0';
            return line;
        }

        // If we reached the end of the buffer but didn't find a newline
        if (index >= bytes_read) 
        {
            index++;
        }
    }
}


void handle_heredoc(t_sh *sh, int x) 
{
    char *line;
    char *delimiter;

    //printf("\n\nENTROU HEREDOC \n\n");   
    line = NULL;
    delimiter = sh->comands[x].inheredoc_file;
    printf("\n\n%s\n", sh->comands[x].inheredoc_file);
    sh->comands[x].inheredoc_file = ft_strdup(".heredoc_temp.txt");
    printf("\n\n%s\n", sh->comands[x].inheredoc_file);
    sh->comands[x].inheredoc_fd = open(sh->comands[x].inheredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (sh->comands[x].inheredoc_fd < 0) {
        perror("Erro ao abrir o arquivo temporário");
        exit(EXIT_FAILURE);
    }

//printf("Digite o texto (terminar com '%s'):\n", delimiter);

    while (1)
    {
        ft_sigset();
        line = get_next_line(0); // Lê da entrada padrão (fd 0)
        if (line == NULL)
        {
            break; // Se houver um erro ou EOF, sai do loop
        }
        // Verifica se a linha lida é o delimitador
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break; // Sai do loop se o delimitador for encontrado
        }
        // Escreve a linha no arquivo
        write(sh->comands[x].inheredoc_fd, line, strlen(line));
        free(line); // Libera a linha lida
    }
    // Fecha o arquivo
    close(sh->comands[x].inheredoc_fd);
    free(delimiter);   
    // Abre o arquivo para leitura e armazena o descritor na estrutur

    // Aqui você pode usar shell->fd_in conforme necessário
    // Por exemplo, você pode redirecionar a entrada padrão para este fd

    // Se você quiser remover o arquivo temporário após o uso, pode usar unlink
    // unlink(temp_filename);
}

