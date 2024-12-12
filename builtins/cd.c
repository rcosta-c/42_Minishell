/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:54:51 by cde-paiv          #+#    #+#             */
/*   Updated: 2024/12/11 17:54:53 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*going_dir_up(char *oldpwd)
{
	int	x;
	int	xx;

	x = 0;
	xx = ft_strlen(oldpwd);
	while (xx > x && oldpwd[xx] != '/')
	{
		oldpwd[xx] = '\0';
		xx--;
	}
	oldpwd[xx] = '\0';
	return (oldpwd);
}

static void	set_dir(t_sh *sh, char *dir)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*old_pwd_var;
	char	*new_pwd_var;

	if (!dir)
	{
		ft_putstr_fd("cd: directory not specified\n", 2);
		sh->error.exit_error = true;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (dir[0] == '.' && dir[1] == '.')
		old_pwd = going_dir_up(old_pwd);
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
	ft_export(sh, (char *[]){ "export", old_pwd_var, NULL });
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
	ft_export(sh, (char *[]){ "export", new_pwd_var, NULL });
	free(new_pwd_var);
	free(new_pwd);
	sh->error.exit_error = false;
}

void	ft_cd(t_sh *sh, char **args)
{
	char	*temp;

	if (args[1] && args[2])
	{
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
