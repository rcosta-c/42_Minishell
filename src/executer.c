/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:18 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/19 10:02:59 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
                g_status = EXIT_FAILURE;
				exit(EXIT_FAILURE);
    		}
		}
		else
			waitpid(pid, NULL, 0);
	}
	g_status = errno;
}


static void	executor_for_one(t_sh *sh, int x)
{
	x = 0;
	if (check_if_builtin(sh->comands[x].cmd))
	{
		handle_redirects(sh, x);
		exec_builtin(sh, x);
	}
	else
	{
		sh->comands[x].cmd = prep_cmd(sh, sh->comands[x].cmd, x);
		if(filter_cmd_error(sh) == true)
			return;
		handle_redirects(sh, x);
		execute_cmd(sh, x);
	}
}

void	executor(t_sh *sh)
{
	if(verify_errors(sh) == true || sh->vars.sh_status == false)
		return;
	if(sh->vars.cmds_num == 0)
		return;
	if(sh->vars.cmds_num == 1)
		executor_for_one(sh, 0);
	else
		check_pipes(sh);
}

