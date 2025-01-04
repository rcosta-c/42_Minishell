/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 00:11:02 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/04 01:06:28 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	verify_error_exit(int option)
{
	if (option == 1)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		g_status = SYNTAX_MISPELL;
	}
	else if (option == 2)
	{
		ft_putstr_fd("> : Permissão recusada: \n", 2);
		g_status = NO_PERMISSION;
	}
	return (true);
}

bool	verify_error_helper(t_sh *sh, int x)
{
	while (x < sh->vars.cmds_num)
	{
		if (sh->comands[x].errors.empty_pipe == true)
			return (verify_error_exit(1));
		else if (sh->comands[x].errors.infile_noaccess == true
			|| sh->comands[x].errors.infile_notvalid == true)
			return (verify_error_exit(2));
		else if (sh->comands[x].errors.outfile_noaccess == true
			|| sh->comands[x].errors.outfile_notvalid == true)
			return (verify_error_exit(2));
		else if (sh->comands[x].errors.empty_redir == true)
			return (verify_error_exit(1));
		else
			x++;
	}
	return (false);
}

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
