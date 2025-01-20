/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:26:11 by mota              #+#    #+#             */
/*   Updated: 2025/01/20 12:08:58 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	echo_exit(t_sh *sh)
{
	sh->error.exit_error = false;
	g_status = EXIT_SUCCESS;
}

void	ft_echo(t_sh *sh, char **args)
{
	int	i;
	int	n_flag;
	int	x;

	x = 0;
	i = 1;
	n_flag = 0;
	while (args[i] && !ft_strncmp(args[i], "-", 1))
	{
		while (args[i][x] == '-')
			x++;
		if (args[i][x] == 'n')
			n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	echo_exit(sh);
}
