/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:59:34 by mota              #+#    #+#             */
/*   Updated: 2024/12/26 11:53:50 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_sh *sh, char **args)
{
	size_t	i;
	char	*temp;

	(void)args;
	i = 0;
	while (sh->envp && ft_strncmp(sh->envp[i], "PWD=", 4))
		i++;
	if (sh->envp && sh->envp[i])
	{
		temp = ft_substr(sh->envp[i], 4, ft_strlen(sh->envp[i]));
		ft_putstr_fd(temp, 1);
		ft_putstr_fd("\n", 1);
		free(temp);
	}
	else
	{
		g_status = BUILTINSERROR;
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		sh->error.exit_error = true;
	}
}

