/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:16:01 by mota              #+#    #+#             */
/*   Updated: 2025/01/09 10:29:35 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	check_wrong_args(char **args)
{
	int	x;
	int	xx;

	xx = 0;
	if (!args[1])
	{
		g_status = 0;
		return (true);
	}
	while (args[xx])
	{
		x = 0;
		while (args[xx][x])
		{
			if (args[xx][x] == '=')
			{
				printf("unset: %s: invalid parameter name\n", args[xx]);
				return (true);
			}
			x++;
		}
		xx++;
	}
	return (false);
}

static void	exit_unset(t_sh *sh, int j, char **envx)
{
	envx[j] = NULL;
	free_env(sh);
	sh->envp = envx;
	sh->vars.envp_total--;
}

static int	get_var_pos_unset(t_sh *sh, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	if (len <= 0)
		return (-1);
	while (i < sh->vars.envp_total)
	{
		if (!ft_strncmp(sh->envp[i], var, len) && sh->envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static bool	check_options(t_sh *sh, char **args)
{
	int	i;

	i = 1;
	if (args[i])
	{
		while (args[i] && !ft_strncmp(args[i], "-", 1))
		{
			if (ft_strlen(args[i]) >= 2 && args[i][0] == '-')
			{
				ft_putstr_fd("unset: options not allowed\n", 2);
				sh->error.exit_error = true;
				return (true);
			}
			i++;
		}
	}
	return (false);
}

void	ft_unset(t_sh *sh, char **args)
{
	int		i;
	int		j;
	char	**envx;

	i = 0;
	j = 0;
	if (check_wrong_args(args) == true || check_options(sh, args) == true)
		return ;
	if (get_var_pos_unset(sh, args[1]) == -1)
		return ;
	envx = malloc(sizeof(char *) * (sh->vars.envp_total));
	if (!envx)
		return ;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], args[1], ft_strlen(args[1])) != 0
			|| sh->envp[i][ft_strlen(args[1])] != '=')
		{
			envx[j] = ft_strdup(sh->envp[i]);
			j++;
		}
		i++;
	}
	exit_unset(sh, j, envx);
}
