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
			if (execve(sh->comands[x].cmd, sh->comands[x].arg, sh->envp) == -1)
			{
                perror("Erro ao executar comando");
                exit(EXIT_FAILURE);
    		}
			g_status = EXIT_SUCCESS;
		}
		else
			waitpid(pid, NULL, 0);
	}
}


static void	executor_for_one(t_sh *sh, int x)
{
	x = 0;
	handle_redirects(sh, x);
	if (check_if_builtin(sh->comands[x].cmd))
		exec_builtin(sh, x);
	else
	{
		sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
		execute_cmd(sh, x);
	}
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
}
/*void	executor_for_lot(t_sh *sh, int x)
{
	while(x < sh->vars.cmds_num)
	{
		if (check_if_builtin(sh->comands[x].cmd))
			exec_builtin(sh, x);
		else
		{
			sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
			execute_multi_cmd(sh, x);
		}
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
	}
}*/

void	executor(t_sh *sh)
{
	int 	x;

	x = 0;
	if(verify_errors(sh) == true || sh->vars.sh_status == false)
		return;
	if(sh->vars.cmds_num == 0)
		return;
	if(sh->vars.cmds_num == 1)
		executor_for_one(sh, x);
	else
	{
		handle_redirects(sh, x);
		check_pipes(sh);		
	}
}
