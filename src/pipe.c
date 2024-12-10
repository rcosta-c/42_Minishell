#include "../includes/minishell.h"

void    close_pipe_child(t_sh *sh)
{
    int  x;
    
    x = 0;
    if(sh->vars.pipe_num == 0)
    return;

     while (x < sh->vars.pipe_num) 
     {
        close(sh->comands[x].pipe_fd[0]);
           close(sh->comands[x].pipe_fd[1]);

        x++;
     }

}

void    start_pipes(t_sh *sh)
{
    int x;

    x = 0;
    while(x < sh->vars.pipe_num)
    {
        if (pipe(sh->comands[x + 1].pipe_fd) == -1) // ALTEREI AQUI PARA X + 1
        {
            perror("Erro ao criar pipe");
            exit(EXIT_FAILURE);
        }
        x++;
    }
}

// funcao para criar os pipes
void create_pipes(t_sh *sh, int **pipes)
{
    int i;

    i = 0;
    pipes = malloc(sizeof(int *) * sh->vars.pipe_num);
    if (!pipes)
        exit(EXIT_FAILURE);
    while (i < sh->vars.pipe_num)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
            exit(EXIT_FAILURE);

        if (pipe(pipes[i]) == -1)
            exit(EXIT_FAILURE);
        i++;
    }
}

// funcao para fechar e liberar os pipes
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

// funcao para configurar os pipes
void setup_pipes(int **pipes, int cmds_num)
{
    int i;

    i = 0;
    if (i == 0) // primeiro comando
        dup2(pipes[i][1], STDOUT_FILENO);
    else if (i == cmds_num - 1) // ultimo comando
        dup2(pipes[i - 1][0], STDIN_FILENO);
    else
    {
        dup2(pipes[i - 1][0], STDIN_FILENO);
        dup2(pipes[i][1], STDOUT_FILENO);
    }
    // fechar todos os pipes apos configurar
    i = 0;
    while (i < cmds_num - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

// funcao principal de execucao
void execute_pipeline(t_sh *sh)
{
    int i;
    int **pipes;
    pid_t pid;
    int status;
    t_exec  *cmd;

    i = 0;
    pipes = NULL;
    create_pipes(sh, pipes);
    while (i < sh->vars.cmds_num)
    {
        cmd = &sh->comands[i];
        pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);
        if (pid == 0) // processo filho
        {
            setup_pipes(pipes, sh->vars.cmds_num);
            if (execve(cmd->cmd, cmd->arg, sh->envp) == -1) // substituir execve pelos dados reais de sh->comands
                exit(EXIT_FAILURE);
        }
        else // processo pai
        {
            if (i < sh->vars.cmds_num - 1)
                close(pipes[i][1]); // fecha a escrita do pipe
        }
        i++;
    }
    close_pipes(pipes, sh->vars.pipe_num);
    while (wait(&status) > 0); // aguarda todos os filhos
}
void check_pipes(t_sh *sh)
{
    int i;

    sh->vars.pipe_num = 0;
    sh->vars.is_pipe = false;
    i = 0;
    while (i < sh->vars.tk_num - 1) // percorre os tokens ate o final do comando
    {
        if (strcmp(sh->tokens[i].tokens, "|") == 0) // verifica se o token atual e um pipe
        {
            sh->vars.pipe_num++;      // incrementa o numero de pipes
            sh->vars.is_pipe = true;  // marca que ha um pipe
            execute_pipeline(sh);
            return ;
        }
        i++;
    }
}