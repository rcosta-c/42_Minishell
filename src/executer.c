#include "../includes/minishell.h"

void    execute_cmd(t_sh *sh, int x)
{
	pid_t	pid;

	if(check_exec_error(sh, x))
		return;
	else
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if(pid == 0)
		{
			//printf("\n\nvai executor o camando...\n");
			if (execve(sh->comands[x].cmd, sh->comands[x].arg, sh->envp) == -1)
			{
                perror("Erro ao executar comando");
				//printf("\n\n SAIU COM ERRO\n\n");
                exit(EXIT_FAILURE);
    		}
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void    execute_multi_cmd(t_sh *sh, int x)
{
	pid_t	pid;

//printf("\n\n entrou em MULTIEXEC\n\n");
	if(check_exec_error(sh, x))
	{
//printf("\n\nFOUDASE! foi aqui que deu merda!\n\n");
		return;
	}
	else
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if(pid == 0)
		{
			if(x > 0)
			{
				dup2(sh->comands[x].pipe_fd[0], STDIN_FILENO);
		        close(sh->comands[x].pipe_fd[0]);

			}
			if(x < sh->vars.pipe_num)
			{
				dup2(sh->comands[x].pipe_fd[1], STDOUT_FILENO);
				close(sh->comands[x].pipe_fd[1]);
			}
			if (execve(sh->comands[x].cmd, sh->comands[x].arg, sh->envp) == -1)
			{
                perror("Erro ao executar comando");
                exit(EXIT_FAILURE);
            }
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void	executor(t_sh *sh)
{
	int 	x;

	x = 0;
	
	//free_for_executer(sh);
	if(verify_errors(sh) == true || sh->vars.sh_status == false)
	{
		printf("%d", sh->vars.sh_status);
		printf("\nMERDA:SAIU AQUI!\n");
		return;
	}
	if(sh->vars.cmds_num == 0)
		return;
	if(sh->vars.cmds_num == 1)
	{
//printf("\n\n\n ENTROU NO EXEC CMD SO 1\n\n");
		handle_redirects(sh, x); //APARTIR DAQUI
//printf("\nJA SAIUDO DOS REDIREEC NO EXEC\n");
		if (check_if_builtin(sh->comands[x].cmd))
		{
			exec_builtin(sh, x);
//printf("Built-in Motherfucker!\n");
		}
		else
		{
			sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
			execute_cmd(sh, x);
		}
		if (sh->comands[x].inbackup != -1) 
		{
//printf("\nentrou na limpeza\n");
			dup2(sh->comands[x].inbackup, STDIN_FILENO);
			//dup2(sh->comands[x].infile_fd, sh->comands[x].inbackup);
			sh->comands[x].infile_fd = -1;
        	close(sh->comands[x].inbackup);
    	}
		if (sh->comands[x].outbackup != -1) 
		{
			dup2(sh->comands[x].outbackup, STDOUT_FILENO);
//			dup2(sh->comands[x].outfile_fd, sh->comands[x].outbackup);
			sh->comands[x].outfile_fd = -1;

        	close(sh->comands[x].outbackup);
    	}	
	}
	else
	{

		handle_redirects(sh, x);

		//start_pipes(sh);
		check_pipes(sh);


		/*while(x < sh->vars.cmds_num)
		{
			//printf("numero_comandos=%d\n\n", sh->vars.cmds_num);
			if (check_if_builtin(sh->comands[x].cmd))
			{
				exec_builtin(sh, x);
//printf("Built-in MULTIIII Motherfucker!\n");
			}
			else
			{
				sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
				execute_multi_cmd(sh, x);
			}
//printf("\nMULTI ARGS -> CMD NUMBER = %d \n", x);
			if (sh->comands[x].inbackup != -1) 
			{
				dup2(sh->comands[x].inbackup, STDIN_FILENO);
				sh->comands[x].infile_fd = -1;
				close(sh->comands[x].inbackup);
    		}
			if (sh->comands[x].outbackup != -1) 
			{
				dup2(sh->comands[x].outbackup, STDOUT_FILENO);
				sh->comands[x].outfile_fd = -1;
				close(sh->comands[x].outbackup);
			}	
			x++;

		}*/	
	}
}




// ATENCAO FALTA ALTERAR A FORMAR COMO GUARDAMOS O INPUT_FD e OUTPUT_FD
	// TENHO DE GUARDAR O FD TAMBEM


// garantir que se existir uma falha na construcao da arvore de processos, a execucao nao segue, e é da mensagem de erro


// verificar o numero de comandos. se um a arvore é simples. se mais a arvore é "recursiva"


//  Verificar se comandos sao builtins, se sim mas nem todos sao criar fork()->> processo independente, fora do nosso programa para executor comandos exteriores


// Verificar se tem pipes para construir a execucao de cada comando.


// (talvez tenha de alterar a definicao do r_in e r_out para int, para passar a guardar o fileno/fd ja que vao ser ficheiros)


// verificar se tem pipes, e nesse caso porque o numero de comandos é maior que 1


// caso exista pipes, criar entao arvore de contrucao de processo.
