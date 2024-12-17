/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:55:12 by cde-paiv          #+#    #+#             */
/*   Updated: 2024/12/17 10:15:01 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
static void	invalid_exit_arg(char *arg, t_sh *sh)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_exit(sh);
	exit(255);
}

void	ft_exit(t_sh *sh, char **args)
{
	int	exit_code;

	if (g_status != -1)
		exit_code = g_status;
	if (!args)
	{
		free_exit(sh);
		exit(exit_code);
	}
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		sh->error.exit_error = true;
		return ;
	}
	if (args[1] && !is_valid_number(args[1]))
		invalid_exit_arg(args[1], sh);
	if (args[1])
		exit_code = ft_atoi(args[1]);
	else
		exit_code = 0;
	free_exit(sh);
	exit(exit_code);
}
