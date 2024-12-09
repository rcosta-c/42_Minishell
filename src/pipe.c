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
