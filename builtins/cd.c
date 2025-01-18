/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:54:51 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/17 17:07:37 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	change_directory(t_sh *sh, char *dir, char *old_pwd)
{
	if (chdir(dir) != 0)
	{
		g_status = BUILTINSERROR;
		perror("cd");
		free(old_pwd);
		sh->error.exit_error = true;
		return (false);
	}
	return (update_old_pwd(sh, old_pwd));
}

static bool	update_new_pwd(t_sh *sh, char *new_pwd)
{
	char	*new_pwd_var;
	char	**temp;

	new_pwd_var = ft_strjoin("PWD=", new_pwd);
	if (!new_pwd_var)
	{
		g_status = BUILTINSERROR;
		free(new_pwd);
		sh->error.exit_error = true;
		return (false);
	}
	temp = malloc(sizeof(char **) * 3);
	temp[0] = ft_strdup("export");
	temp[1] = ft_strdup(new_pwd_var);
	temp[2] = NULL;
	ft_export(sh, temp);
	free(sh->vars.sh_pwd);
	sh->vars.sh_pwd = verify_home(sh, new_pwd);
	free(new_pwd_var);
	free(temp[0]);
	free(temp[1]);
	free(temp);
	return (true);
}

static bool	handle_new_pwd(t_sh *sh)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		g_status = BUILTINSERROR;
		sh->error.exit_error = true;
		return (false);
	}
	return (update_new_pwd(sh, new_pwd));
}

void	set_dir(t_sh *sh, char *dir)
{
	char	*old_pwd;

	if (!dir)
	{
		g_status = BUILTINSERROR;
		ft_putstr_fd("cd: directory not specified\n", 2);
		sh->error.exit_error = true;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (!change_directory(sh, dir, old_pwd))
		return ;
	if (!handle_new_pwd(sh))
		return ;
	sh->error.exit_error = false;
}

void	ft_cd(t_sh *sh, char **args)
{
	char	*temp;

	if (args[1] && args[2])
	{
		g_status = BUILTINSERROR;
		ft_putstr_fd("cd: too many arguments\n", 2);
		sh->error.exit_error = true;
	}
	else if (args[1])
		set_dir(sh, args[1]);
	else
	{
		temp = search_envp(sh, "HOME");
		set_dir(sh, temp);
		free(temp);
	}
}
