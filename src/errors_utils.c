/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 23:50:16 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/04 01:06:06 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	check_file(char **arg, int xx)
{
	int	x;

	x = 0;
	if (!arg[xx])
		return (false);
	while (arg[xx][x] != '\0')
	{
		if (arg[xx][x] == '.')
			return (true);
		x++;
	}
	return (false);
}

bool	check_special_case(t_sh *sh, int x)
{
	int			xx;
	struct stat	file_info;

	xx = 0;
	while (sh->comands[x].n_args >= 1 && xx < sh->comands[x].n_args)
	{
		if (stat(sh->comands[x].arg[xx + 1], &file_info) == -1)
		{
			if (check_file(sh->comands[x].arg, xx + 1) == true)
			{
				if (errno == ENOENT)
				{
					ft_putstr_fd(" No such file or directory\n", 2);
					g_status = BUILTINSERROR;
					return (true);
				}
			}
		}
		xx++;
	}
	return (false);
}

bool	check_access_error(t_sh *sh, int x)
{
	if (check_special_case(sh, x) == true)
		return (true);
	if (access(sh->comands[x].cmd, F_OK) == 0)
	{
		if (access(sh->comands[x].cmd, X_OK) != 0)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			g_status = NO_PERMISSION;
			return (true);
		}
	}
	return (false);
}

bool	check_file_error(t_sh *sh, int x)
{
	struct stat	path_stat;

	if (stat(sh->comands[x].cmd, &path_stat) == 0
		&& access(sh->comands[x].cmd, X_OK) == 0
		&& access(sh->comands[x].cmd, F_OK) == 0)
		return (false);
	if ((sh->comands[x].cmd[0] == '/') || (sh->comands[x].cmd[0] == '.'))
	{
		sh->comands[x].errors.cmd_not_found = true;
		ft_putstr_fd(" No such file or directory\n", 2);
		g_status = CMD_NOT_FOUND;
		return (true);
	}
	sh->comands[x].errors.cmd_not_found = true;
	ft_putstr_fd(" command not found\n", 2);
	g_status = CMD_NOT_FOUND;
	return (true);
}

bool	check_env_var_error(t_sh *sh, int x)
{
	char	*env_var;

	if (sh->comands[x].cmd[0] == '$')
	{
		env_var = getenv(&sh->comands[x].cmd[1]);
		if (!env_var || !*env_var)
		{
			ft_putstr_fd("Minishell: variável de ambiente não \
				resolvida:", 2);
			ft_putstr_fd(sh->comands[x].cmd, 2);
			ft_putstr_fd("\n", 2);
			g_status = ENV_VAR_NOT_FOUND;
			return (true);
		}
	}
	return (false);
}
