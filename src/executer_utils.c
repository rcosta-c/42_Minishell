/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:24 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 09:18:53 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_exec_error(t_sh *sh, int x)
{
	if (sh->comands[x].errors.cmd_not_found == true)
	{
		printf("%s: command not found\n", sh->comands[x].cmd);
		g_status = CMD_NOT_FOUND;
		return(true);
	}
	else if (sh->comands[x].errors.empty_pipe == true)
	{
		printf("%s empty pipe not allowed\n", sh->comands[x].cmd);
		g_status = WRONG_SYNTAX;
		return(true);
	}
	else if (sh->comands[x].errors.infile_noaccess == true || sh->comands[x].errors.infile_notvalid == true)
	{
		printf("%s: access to file denied\n", sh->comands[x].cmd);
		g_status = NO_PERMISSION;
		return(true);
	}
	else if (sh->comands[x].errors.outfile_noaccess == true || sh->comands[x].errors.outfile_notvalid == true)
	{
		printf("%s: access to file denied\n", sh->comands[x].cmd);
		g_status = NO_PERMISSION;
		return(true);
	}
	return(false);
}

bool	check_if_builtin(char *cmd)
{
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		return(true);
	else if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		return(true);
	else if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		return(true);
	else if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		return(true);	
	else if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		return(true);
	else if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		return(true);	
	else if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		return(true);	
	else
		return(false);
}

void    exec_builtin(t_sh *sh, int cmd_nbr)
{
	if (ft_strncmp("echo", sh->comands[cmd_nbr].cmd, ft_strlen("echo")) == 0)
		ft_echo(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("cd", sh->comands[cmd_nbr].cmd, ft_strlen("cd")) == 0)
		ft_cd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("pwd", sh->comands[cmd_nbr].cmd, ft_strlen("pwd")) == 0)
		ft_pwd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("export", sh->comands[cmd_nbr].cmd, ft_strlen("export")) == 0)
		ft_export(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("unset", sh->comands[cmd_nbr].cmd, ft_strlen("unset")) == 0)
		ft_unset(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("env", sh->comands[cmd_nbr].cmd, ft_strlen("env")) == 0)
		ft_env(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("exit", sh->comands[cmd_nbr].cmd, ft_strlen("exit")) == 0)
		ft_exit(sh, sh->comands[cmd_nbr].arg);
}

static char		*prep_cmd_helper(char *temp, char **path, char *cmd)
{
	int 		x;
	struct stat	path_stat;

	x = 0;
	if(stat(temp, &path_stat) == 0 && access(temp, X_OK) == 0 && access(temp, F_OK) == 0)
		x = 0;
	else
	{
		while(path[x])
		{
			free(temp);
			temp = ft_strjoin(path[x], cmd);
			if(stat(temp, &path_stat) == 0 && access(temp, X_OK) == 0 && access(temp, F_OK) == 0)
				break;
			x++;
		}
		if (!path[x])
		{
			free(temp);
			temp = ft_strdup(cmd);	
		}
	}
	return(temp);
}

char    *prep_cmd(t_sh *sh, char *cmd, int xx)
{
	char	**path;
	char	*temp;
	int x;

	x = 0;
//printf("\n\n   AGORA AQUI ESTA XX = %d, cmd = %s ", xx, cmd);
	if(cmd[x] == '/')
	{
		if(access(cmd, X_OK) != 0 && access(cmd, F_OK) != 0)
			sh->comands[xx].errors.cmd_not_found = true;
		return(cmd);
	}
	path = ft_split(getenv("PATH"), ':');
	temp = ft_strjoin("/bin/", cmd);
	temp = prep_cmd_helper(temp, path, cmd);
	x = -1;
	while(path[++x])
		free(path[x]);
	free(path);
	free(cmd);
	return(temp);
}

