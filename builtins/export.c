/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:08:39 by mota              #+#    #+#             */
/*   Updated: 2024/12/18 10:19:18 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_var_pos(t_sh *sh, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strchr(var, '=') - var;
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

static void	update_var(t_sh *sh, char *var)
{
	int		var_pos;
	int		i;
	int		new_size;
	char	**envp_temp;

	var_pos = get_var_pos(sh, var);
	if (var_pos >= 0)
	{
		free(sh->envp[var_pos]);
		sh->envp[var_pos] = ft_strdup(var);
		return ;
	}
	new_size = sh->vars.envp_total + 2;
	envp_temp = ft_calloc(new_size, sizeof(char *));
	if (!envp_temp)
	{
		free(envp_temp);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < sh->vars.envp_total)
	{
		envp_temp[i] = ft_strdup(sh->envp[i]);
		if (!envp_temp[i])
		{
			free(envp_temp);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	envp_temp[i] = ft_strdup(var);
	if (!envp_temp[i])
	{
		free(envp_temp);
		exit(EXIT_FAILURE);
	}
	sh->vars.envp_total++;
	free_env(sh);
	sh->envp = envp_temp;
}

static int	valid_var(char *var)
{
	int	i;

	if (!var || var[0] == '=' || ft_isdigit(var[0]))
		return (0);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_sh *sh, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (valid_var(args[i]))
		{
			if (ft_strchr(args[i], '='))
			{
				update_var(sh, args[i]);
				sh->error.exit_error = false;
			}
		}
		else
		{
			ft_putstr_fd(": export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			sh->error.exit_error = true;
		}
		i++;
	}
	if (!args[1])
	{
		i = 0;
		while (sh->envp[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sh->envp[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		sh->error.exit_error = false;
	}
}
