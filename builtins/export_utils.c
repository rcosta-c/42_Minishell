/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:26:43 by mota              #+#    #+#             */
/*   Updated: 2024/12/30 11:27:23 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	display_info(char *equal_sign, char **temp, int i)
{
	ft_putstr_fd("declare -x ", 1);
	write(1, temp[i], equal_sign - temp[i] + 1);
	ft_putchar_fd('"', 1);
	ft_putstr_fd(equal_sign + 1, 1);
	ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
}

void	display_exported_vars(t_sh *sh)
{
	int		i;
	char	*equal_sign;
	char	**temp;

	i = 0;
	temp = handle_array(sh);
	while (sh->envp[i])
	{
		equal_sign = ft_strchr(temp[i], '=');
		if (equal_sign)
			display_info(equal_sign, temp, i);
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(temp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	free_temp_env(temp);
}

int	get_var_pos(t_sh *sh, char *var)
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

static void	create_new_var(t_sh *sh, char *var)
{
	char	**envp_temp;
	int		i;
	int		new_size;

	new_size = sh->vars.envp_total + 2;
	envp_temp = ft_calloc(new_size, sizeof(char *));
	if (!envp_temp)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < sh->vars.envp_total)
	{
		envp_temp[i] = ft_strdup(sh->envp[i]);
		if (!envp_temp[i])
			exit(EXIT_FAILURE);
		i++;
	}
	envp_temp[i] = ft_strdup(var);
	if (!envp_temp[i])
		exit(EXIT_FAILURE);
	sh->vars.envp_total++;
	free_env(sh);
	sh->envp = envp_temp;
}

void	update_var(t_sh *sh, char *var)
{
	int	var_pos;

	var_pos = get_var_pos(sh, var);
	if (var_pos >= 0)
	{
		free(sh->envp[var_pos]);
		sh->envp[var_pos] = ft_strdup(var);
		return ;
	}
	create_new_var(sh, var);
}
