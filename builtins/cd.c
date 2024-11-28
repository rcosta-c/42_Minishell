#include "../includes/minishell.h"

// Altera o diretório de trabalho e atualiza PWD e OLDPWD
static void	set_dir(t_sh *sh, char *dir)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*old_pwd_var;
	char	*new_pwd_var;
	char	*args[3];

	if (!dir)
	{
		ft_putstr_fd("cd: directory not specified\n", 2);
		sh->error.exit_error = true;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		free(old_pwd);
		sh->error.exit_error = true;
		return ;
	}
	if (chdir(dir) != 0)
	{
		perror("cd");
		free(old_pwd);
		sh->error.exit_error = true;
		return ;
	}
	old_pwd_var = ft_strjoin("OLDPWD=", old_pwd);
	if (!old_pwd_var)
	{
		free(old_pwd);
		sh->error.exit_error = true;
		return ;
	}
	args[0] = "export";
	args[1] = old_pwd_var;
	args[2] = NULL;
	ft_export(sh, args);
	free(old_pwd_var);
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		sh->error.exit_error = true;
		return ;
	}
	new_pwd_var = ft_strjoin("PWD=", new_pwd);
	if (!new_pwd_var)
	{
		free(new_pwd);
		sh->error.exit_error = true;
		return ;
	}
	args[0] = "export";
	args[1] = new_pwd_var;
	args[2] = NULL;
	ft_export(sh, args);
	free(new_pwd_var);
	free(new_pwd);
	sh->error.exit_error = false;
}

// Retorna o valor da variável HOME ou NULL se não existir
static char	*set_home(t_sh *sh)
{
	char	*home;
	int		i;

	i = 0;
	home = NULL;
	while (sh->envp && sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], "HOME=", 5) == 0)
		{
			home = ft_strdup(sh->envp[i] + 5);
			break ;
		}
		i++;
	}
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		sh->error.exit_error = true;
	}
	return (home);
}

// Implementa o builtin cd
void	ft_cd(t_sh *sh, char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		sh->error.exit_error = true;
	}
	else if (args[1])
		set_dir(sh, args[1]);
	else
		set_dir(sh, set_home(sh));
}
