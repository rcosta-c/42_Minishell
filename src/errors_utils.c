/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 23:50:16 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/31 00:15:17 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_directory_error(t_sh *sh, int x)
{
	struct stat	path_stat;

	if (stat(sh->comands[x].cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		if (ft_isalpha(sh->comands[x].cmd[0]))
		{
			sh->comands[x].errors.cmd_not_found = true;
			ft_putstr_fd(" command not found\n", 2);
			g_status = CMD_NOT_FOUND;
			return (true);
		}
		ft_putstr_fd("  Is a directory\n", 2);
		g_status = NO_PERMISSION;
		return (true);
	}
	return (false);
}

bool	filter_tk_error_exit(t_sh *sh)
{
	g_status = SYNTAX_MISPELL;
	sh->vars.sh_status = false;
	return (true);
}

bool	check_access_error(t_sh *sh, int x)
{
	if (access(sh->comands[x].cmd, F_OK) == 0)
	{
		if (access(sh->comands[x].cmd, X_OK))
		{
			ft_putstr_fd(" Permission denied\n", 2);
			g_status = NO_PERMISSION;
			return (true);
		}
		return (false);
	}
	return (false);
}

bool	check_file_error(t_sh *sh, int x)
{
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
