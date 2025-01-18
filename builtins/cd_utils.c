/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:29:46 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/17 16:41:34 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*going_dir_up(char *oldpwd)
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

bool	update_old_pwd(t_sh *sh, char *old_pwd)
{
	char	*old_pwd_var;
	char	**temp;

	old_pwd_var = ft_strjoin("OLDPWD=", old_pwd);
	if (!old_pwd_var)
	{
		g_status = BUILTINSERROR;
		free(old_pwd);
		sh->error.exit_error = true;
		return (false);
	}
	temp = malloc(sizeof(char **) * 3);
	temp[0] = ft_strdup("export");
	temp[1] = ft_strdup(old_pwd_var);
	temp[2] = NULL;
	ft_export(sh, temp);
	free(old_pwd_var);
	free(old_pwd);
	free(temp[0]);
	free(temp[1]);
	free(temp);
	return (true);
}
