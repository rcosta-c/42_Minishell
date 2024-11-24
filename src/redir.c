#include "../includes/minishell.h"

void	handle_redirects(t_sh *sh, int x)
{
	if (sh->comands[x].infile)
	{
         	close(sh->comands[x].infile_fd);

        printf("\nvai fazer infile_fd open!\n\n");
		sh->comands[x].infile_fd = open(sh->comands[x].infile, O_RDONLY);
		if (sh->comands[x].infile_fd < 0) 
		{
            printf("\n\n CORREU MAL CARALHO infile_fd open!\n\n");
			sh->comands[x].errors.infile_notvalid = true;
			perror("Erro ao abrir input_fd");
			return;
		}
        dup2(sh->comands[x].infile_fd, STDIN_FILENO);
        //dup(sh->comands[x].infile_fd);
       	close(sh->comands[x].infile_fd);

        
        
        printf("ACABU DE FAZER DUP2\n\n\n");


	}
	if (sh->comands[x].outfile)
	{
    	close(sh->comands[x].outfile_fd);

                printf("\nvai fazer OUTfile_fd open!\n\n");

		sh->comands[x].outfile_fd = open(sh->comands[x].outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(sh->comands[x].outfile_fd < 0)
		{
                        printf("\n\n CORREU MAL CARALHO OUT_FD open!\n\n");

			sh->comands[x].errors.outfile_notvalid = true;
			perror("erro ao abrir output_fd");
			return;
		}
	}
}

/*void	ft_redir_in(t_sh *sh, int x)
{
	int	i;

	i = 0;
    if()




	while (i < cmd->n_in)
	{
		if (cmd->in_fd != -1 && i > 0)
		{
			close(cmd->in_fd);
			if (cmd->in[i - 1].type == RD_IN_HD)
				unlink(cmd->in[i - 1].name);
			cmd->in_fd = -1;
		}
		cmd->in_fd = ft_redir_in_type(cmd->in + i);
		i++;
	}
	if (cmd->in_fd < 0)
		ft_fork_exit(sh, NULL, FAILURE);
	if (ft_pipe_setter_fd(sh, cmd->in_fd, STDIN_FILENO) == PIPE_FAIL)
	{
		close(cmd->in_fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}
*/