#include "../includes/minishell.h"

// funcao para criar os pipes
void create_pipes(t_sh *sh, int ***pipes)
{
    int i;

    *pipes = malloc(sizeof(int *) * sh->vars.pipe_num);
    if (!*pipes)
        exit(EXIT_FAILURE);
    i = 0;
    while (i < sh->vars.pipe_num)
    {
        (*pipes)[i] = malloc(sizeof(int) * 2);
        if (!(*pipes)[i])
            exit(EXIT_FAILURE);
        if (pipe((*pipes)[i]) == -1)
            exit(EXIT_FAILURE);
        i++;
    }
}

void close_pipes(int **pipes, int pipe_num)
{
    int i;

    i = 0;
    while (i < pipe_num)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

void setup_pipes(int **pipes, int i, int cmds_num)
{
    if (i == 0) // Primeiro comando
        dup2(pipes[i][1], STDOUT_FILENO);
    else if (i == cmds_num - 1) // Último comando
        dup2(pipes[i - 1][0], STDIN_FILENO);
    else
    {
        dup2(pipes[i - 1][0], STDIN_FILENO);
        dup2(pipes[i][1], STDOUT_FILENO);
    }
    // Fechar os pipes para evitar vazamentos
    for (int j = 0; j < cmds_num - 1; j++)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
}

void execute_pipeline(t_sh *sh, int n_cmds)
{
    int i, pipefd[2], in_fd = 0;

    for (i = 0; i < n_cmds; i++)
    {
        pipe(pipefd); // Cria um par de file descriptors para o pipe

        if (fork() == 0)
        {
            dup2(in_fd, 0); // Redireciona entrada padrão
            if (i < n_cmds - 1)
                dup2(pipefd[1], 1); // Redireciona saída padrão para o pipe

            close(pipefd[0]); // Fecha leitura do pipe
            execvp(sh->comands[i].cmd, sh->comands[i].arg); // Executa o comando
            perror("execvp"); // Caso falhe, exibe erro
            exit(EXIT_FAILURE);
        }

        // Fecha o pipe atual e ajusta o in_fd para o próximo comando
        close(pipefd[1]);
        in_fd = pipefd[0];
    }

    // Aguarda todos os processos filhos
    for (i = 0; i < n_cmds; i++)
        wait(NULL);
}

void check_pipes(t_sh *sh)
{
    int i;

    sh->vars.pipe_num = 0;
    sh->vars.is_pipe = false;

    i = 0;
    while (i < sh->vars.tk_num - 1)
    {
        if (strcmp(sh->tokens[i].tokens, "|") == 0)
        {
            sh->vars.pipe_num++;
            sh->vars.is_pipe = true;
        }
        i++;
    }

    if (sh->vars.is_pipe)
        execute_pipeline(sh, sh->vars.cmds_num);
}
