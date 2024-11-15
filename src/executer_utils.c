#include "../includes/minishell.h"

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
/*
void    exec_builtin(t_sh *sh, int  cmd_nbr)
{
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		ft_echo(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		ft_cd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		ft_pwd(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		ft_export(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		ft_unset(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		ft_env(sh, sh->comands[cmd_nbr].arg);
	else if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		ft_exit(sh, sh->comands[cmd_nbr].arg);
	else
		return(false);
}*/

char    *prep_cmd(char *cmd)
{
	char	*dest;

	dest = join_2_str("/bin/", cmd, NULL);
	free(cmd);
	return(dest);
}
