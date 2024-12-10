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

void wait_for_children(int cmds_num)
{
    int count = 0;
    int status;

    while (count < cmds_num)
    {
        if (wait(&status) < 0)
        {
            perror("wait");
            break ;
        }
        count++;
    }
}


void execute_pipeline(t_sh *sh, t_exec *cmd)
{
    int i;
    int pipe_fd[2];
    int pid;

	i = 0;
    while (i < sh->vars.cmds_num)
    {
        cmd = &sh->comands[i];
        if (i < sh->vars.cmds_num - 1)
        {
            if (pipe(pipe_fd) < 0)
            {
                perror("pipe");
                sh->error.exec_error = true;
                return;
            }
            cmd->pipe_fd[1] = pipe_fd[1];
            sh->comands[i + 1].pipe_fd[0] = pipe_fd[0];
        }
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            sh->error.exec_error = true;
            return;
        }
        if (pid == 0)
        {
            setup_pipes(cmd);
            handle_redirects(sh, cmd);
            execute_cmd(cmd, sh);
        }
        else
        {
            if (cmd->pipe_fd[1] != -1)
                close(cmd->pipe_fd[1]);
        }
        i++;
    }
    wait_for_children(sh->vars.cmds_num);
}
