/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:24 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/08 14:54:50 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	exit_check_exec_error(int option)
{
	if (option == 1)
	{
		g_status = CMD_NOT_FOUND;
	}
	else if (option == 2)
	{
		g_status = WRONG_SYNTAX;
	}
	else if (option == 3)
	{
		g_status = NO_PERMISSION;
	}
	return (true);
}

bool	check_exec_error(t_sh *sh, int x)
{
	if (sh->comands[x].errors.cmd_not_found == true)
	{
		printf("%s: command not found\n", sh->comands[x].cmd);
		return (exit_check_exec_error(1));
	}
	else if (sh->comands[x].errors.empty_pipe == true)
	{
		printf("%s empty pipe not allowed\n", sh->comands[x].cmd);
		return (exit_check_exec_error(2));
	}
	else if (sh->comands[x].errors.infile_noaccess == true
		|| sh->comands[x].errors.infile_notvalid == true)
	{
		printf("%s: access to file denied\n", sh->comands[x].cmd);
		return (exit_check_exec_error(3));
	}
	else if (sh->comands[x].errors.outfile_noaccess == true
		|| sh->comands[x].errors.outfile_notvalid == true)
	{
		printf("%s: access to file denied\n", sh->comands[x].cmd);
		return (exit_check_exec_error(3));
	}
	return (false);
}

static char	*prep_cmd_helper(char *temp, char **path, char *cmd)
{
	int			x;
	struct stat	path_stat;

	x = 0;
	if (!path)
		return (ft_strdup(cmd));
	while (path[x])
	{
		temp = join_2_str(path[x], cmd, "/", 0);
		if (stat(temp, &path_stat) == 0 && access(temp, X_OK) == 0
			&& access(temp, F_OK) == 0)
			break ;
		free(temp);
		x++;
	}
	if (!path[x])
		temp = ft_strdup(cmd);
	return (temp);
}

static void	free_prepcmd(char *temp2, char **path, char *cmd)
{
	int		x;

	x = -1;
	if (path)
	{
		while (path[++x])
			free(path[x]);
	}
	free(temp2);
	free(path);
	free(cmd);
}

char	*prep_cmd(t_sh *sh, char *cmd, int xx)
{
	char	**path;
	char	*temp;
	char	*temp2;

	temp = NULL;
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) != 0 && access(cmd, F_OK) != 0)
			sh->comands[xx].errors.cmd_not_found = true;
		return (cmd);
	}
	temp2 = search_envp(sh, "PATH");
	if (!temp2)
		temp2 = ft_strdup(" :");
	path = ft_split(temp2, ':');
	temp = prep_cmd_helper(temp, path, cmd);
	free_prepcmd(temp2, path, cmd);
	return (temp);
}
