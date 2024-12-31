/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 00:11:02 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/31 00:35:05 by rcosta-c         ###   ########.fr       */
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
