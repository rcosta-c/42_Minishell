#include "../includes/minishell.h"

void    execute_cmd(t_sh *sh, int x)
{
	pid_t	pid;

	if(check_exec_error(sh, x))
		pid = pid;
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
			printf("\n\nvai executor o camando...\n");
				//execvp(sh->comands[x].arg[0], sh->comands[x].arg);
				execve(sh->comands[x].cmd, sh->comands[x].arg, sh->envp);
				//perror("exec failed");
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void	executor(t_sh *sh)
{
	int 	x;

	x = 0;
	
	if(sh->vars.cmds_num == 1)
	{
		if (check_if_builtin(sh->comands[x].cmd))
		{
			exec_builtin(sh, x);
			printf("Built-in Motherfucker!\n");
		}
		else
			sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
			execute_cmd(sh, x);
	}
	else
	{
		while(x < sh->vars.cmds_num)
		{
			printf("numero_comandos=%d\n\n", sh->vars.cmds_num);
			if (check_if_builtin(sh->comands[x].cmd))
			{
				exec_builtin(sh, x);
				printf("Built-in MULTIIII Motherfucker!\n");
			}
			else
			{
				sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
				execute_cmd(sh, x);
			}
			printf("\nMULTI ARGS -> CMD NUMBER = %d \n", x);
			x++;		
			
		}
		
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
