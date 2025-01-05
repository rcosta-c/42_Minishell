/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:24 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/03 09:00:27 by rcosta-c         ###   ########.fr       */
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
	/*if (stat(temp, &path_stat) == 0 && access(temp, X_OK) == 0
		&& access(temp, F_OK) == 0)
		x = 0;
	else
	{*/
		while (path[x])
		{
			free(temp);
			temp = join_2_str(path[x], cmd, "/", 0);
			printf("\nTEMP_no_HELPER %d=%s-fim-\n", x, temp);
			if (stat(temp, &path_stat) == 0 && access(temp, X_OK) == 0
				&& access(temp, F_OK) == 0)
				break ;
			x++;
		}
		if (!path[x])
		{
			free(temp);
			temp = ft_strdup(cmd);
		}
	//}
	return (temp);
}

char	*prep_cmd(t_sh *sh, char *cmd, int xx)
{
	char	**path;
	char	*temp;
	int		x;

	x = 0;
	if (cmd[x] == '/')
	{
		if (access(cmd, X_OK) != 0 && access(cmd, F_OK) != 0)
			sh->comands[xx].errors.cmd_not_found = true;
		return (cmd);
	}
	path = ft_split(getenv("PATH"), ':');
	temp = ft_strjoin("/bin/", cmd);
	temp = prep_cmd_helper(temp, path, cmd);
	x = -1;
	while (path[++x])
		free(path[x]);
	free(path);
	free(cmd);
	return (temp);
}
