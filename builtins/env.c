/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:39:54 by mota              #+#    #+#             */
/*   Updated: 2025/01/10 11:48:06 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	env_exit_error(t_sh *sh, char **args)
{
	int	i;

	i = 1;
	if (args[i] && args[i][0] == '-' && ft_isalnum(args[i][1]))
	{
		sh->error.exit_error = true;
		ft_putstr_fd("env: options not allowed\n", 2);
		return (true);
	}
	return (false);
}

void	ft_env(t_sh *sh, char **args)
{
	size_t	i;

	if (env_exit_error(sh, args) == true)
		return ;
	else if (args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': Arguments and options aren't supported\n", 2);
		sh->error.exit_error = true;
		return ;
	}
	else
	{
		i = 0;
		while (sh->envp[i])
		{
			ft_putstr_fd(sh->envp[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		sh->error.exit_error = false;
	}
}
