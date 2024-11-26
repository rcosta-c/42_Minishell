#include "../includes/minishell.h"

bool	check_exec_error(t_sh *sh, int x)
{
	if (sh->comands[x].errors.cmd_not_found == true)
	{
		printf("Minishell: command not found: %s", sh->comands[x].cmd);
		return(true);
	}
	else if (sh->comands[x].errors.empty_pipe == true)
	{
		printf("Minishell: command not found: %s", sh->comands[x].cmd);
		return(true);
	}
	else if (sh->comands[x].errors.infile_noaccess == true || sh->comands[x].errors.infile_notvalid == true)
	{
		printf("Minishell: command not found: %s", sh->comands[x].cmd);
		return(true);
	}
	else if (sh->comands[x].errors.outfile_noaccess == true || sh->comands[x].errors.outfile_notvalid == true)
	{
		printf("Minishell: command not found: %s", sh->comands[x].cmd);
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
	if (ft_strncmp("echo", sh->comands[cmd_nbr].cmd, ft_strlen(sh->comands[cmd_nbr].cmd)) == 0)
		ft_echo(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("cd", sh->comands[cmd_nbr].cmd, ft_strlen(sh->comands[cmd_nbr].cmd)) == 0)
		ft_cd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("pwd", sh->comands[cmd_nbr].cmd, ft_strlen(sh->comands[cmd_nbr].cmd)) == 0)
		ft_pwd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("export", sh->comands[cmd_nbr].cmd, ft_strlen(sh->comands[cmd_nbr].cmd)) == 0)
		ft_export(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("unset", sh->comands[cmd_nbr].cmd, ft_strlen(sh->comands[cmd_nbr].cmd)) == 0)
		ft_unset(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("env", sh->comands[cmd_nbr].cmd, ft_strlen(sh->comands[cmd_nbr].cmd)) == 0)
		ft_env(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("exit", sh->comands[cmd_nbr].cmd, ft_strlen(sh->comands[cmd_nbr].cmd)) == 0)
		ft_exit(sh, sh->comands[cmd_nbr].arg);
}

char    *prep_cmd(t_sh *sh, char *cmd, int xx)
{
	char	**path;
	char	*temp;
	struct stat	path_stat;
	int x;

	x = 0;
	path = ft_split(getenv("PATH"), ':');
	temp = ft_strjoin("/bin/", cmd);
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
			sh->comands[xx].errors.cmd_not_found = true;
			temp = ft_strdup(cmd);	
		}
	}
	x = -1;
	while(path[++x])
		free(path[x]);
	free(path);
	free(cmd);
	return(temp);
}
