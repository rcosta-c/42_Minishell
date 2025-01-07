/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:59:34 by mota              #+#    #+#             */
/*   Updated: 2025/01/07 22:08:44 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_sh *sh, char **args)
{
	char	*temp;

	if (args[1])
	{
		g_status = BUILTINSERROR;
		ft_putstr_fd("pwd: options not allowed\n", 2);
		sh->error.exit_error = true;
	}
	else if (sh->vars.sh_pwd)
	{
		temp = ft_strjoin(sh->vars.sh_home, (sh->vars.sh_pwd + 1));
		ft_putstr_fd(temp, 1);
		ft_putstr_fd("\n", 1);
		free(temp);
	}
	else
	{
		g_status = BUILTINSERROR;
		ft_putstr_fd("pwd: error retrieving current directory:", 2);
		ft_putstr_fd("getcwd: cannot access parent", 2);
		ft_putstr_fd("directories: No such file or directory\n", 2);
		sh->error.exit_error = true;
	}
}
