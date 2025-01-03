/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:18 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/03 11:09:55 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_sh *sh, int cmd_nbr)
{
	if (ft_strncmp("echo", sh->comands[cmd_nbr].cmd, ft_strlen("echo")) == 0)
		ft_echo(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("cd", sh->comands[cmd_nbr].cmd, ft_strlen("cd")) == 0)
		ft_cd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("pwd", sh->comands[cmd_nbr].cmd, ft_strlen("pwd")) == 0)
		ft_pwd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("export", sh->comands[cmd_nbr].cmd,
			ft_strlen("export")) == 0)
		ft_export(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("unset", sh->comands[cmd_nbr].cmd,
			ft_strlen("unset")) == 0)
		ft_unset(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("env", sh->comands[cmd_nbr].cmd, ft_strlen("env")) == 0)
		ft_env(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("exit", sh->comands[cmd_nbr].cmd,
			ft_strlen("exit")) == 0)
		ft_exit(sh, sh->comands[cmd_nbr].arg);
}

bool	check_if_builtin(char *cmd)
{
	if (ft_strncmp("echo", cmd, ft_strlen("echo")) == 0)
		return (true);
	else if (ft_strncmp("cd", cmd, ft_strlen("cd")) == 0)
		return (true);
	else if (ft_strncmp("pwd", cmd, ft_strlen("pwd")) == 0)
		return (true);
	else if (ft_strncmp("export", cmd, ft_strlen("export")) == 0)
		return (true);
	else if (ft_strncmp("unset", cmd, ft_strlen("unset")) == 0)
		return (true);
	else if (ft_strncmp("env", cmd, ft_strlen("env")) == 0)
		return (true);
	else if (ft_strncmp("exit", cmd, ft_strlen("exit")) == 0)
		return (true);
	else
		return (false);
}

void	execute_cmd(t_sh *sh, int x)
{
	pid_t	pid;

	if (check_exec_error(sh, x))
		return ;
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(sh->comands[x].cmd, sh->comands[x].arg, sh->envp) == -1)
			{
				perror("Error executing command");
				g_status = EXIT_FAILURE;
				exit(EXIT_FAILURE);
			}
			g_status = errno;
		}
		else
			waitpid(pid, NULL, 0);
	}
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
		if (filter_cmd_error(sh) == true)
			return ;
		handle_redirects(sh, x);
		execute_cmd(sh, x);
	}
}

void	executor(t_sh *sh)
{
	if (verify_errors(sh) == true || sh->vars.sh_status == false)
		return ;
	if (sh->vars.cmds_num == 0)
		return ;
	if (sh->vars.cmds_num == 1)
		executor_for_one(sh, 0);
	else
		check_pipes(sh);
}
