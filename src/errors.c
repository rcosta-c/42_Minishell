/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:30 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/31 00:12:16 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	filter_cmd_error(t_sh *sh)
{
	int	x;

	x = 0;
	if (sh->vars.sh_status == false)
		return (true);
	while (x < sh->vars.cmds_num)
	{
		if (check_directory_error(sh, x))
			return (true);
		if (check_access_error(sh, x))
			return (true);
		if (check_file_error(sh, x))
			return (true);
		if (check_env_var_error(sh, x))
			return (true);
		x++;
	}
	return (false);
}

static bool	filter_tkerrors2(t_sh *sh)
{
	if (sh->tokens[0].r_heredoc || sh->tokens[0].r_in
		|| sh->tokens[0].r_out || sh->tokens[0].r_outappend)
	{
		if (ft_strlen(sh->tokens[0].tokens) == 3)
		{
			ft_putstr_fd("  syntax error near unexpected token `>'\n", 2);
			return (filter_tk_error_exit(sh));
		}
		else
		{
			ft_putstr_fd(" syntax error near unexpected token `newline'\n", 2);
			return (filter_tk_error_exit(sh));
		}
	}
	else if (sh->tokens[sh->vars.tk_num - 1].r_heredoc
		|| sh->tokens[sh->vars.tk_num - 1].r_in
		|| sh->tokens[sh->vars.tk_num - 1].r_out
		|| sh->tokens[sh->vars.tk_num - 1].r_outappend)
	{
		ft_putstr_fd(" syntax error near unexpected token `%d'\n", 2);
		return (filter_tk_error_exit(sh));
	}
	return (false);
}

static bool	filter_tkerrors(t_sh *sh)
{
	if (sh->vars.tk_num == sh->vars.pipe_num
		|| sh->tokens[0].pipe == true)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		g_status = SYNTAX_MISPELL;
		sh->vars.sh_status = false;
		return (true);
	}
	else if (sh->tokens[sh->vars.tk_num - 1].pipe == true)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		g_status = SYNTAX_MISPELL;
		sh->vars.sh_status = false;
		return (true);
	}
	else
		filter_tkerrors2(sh);
	return (false);
}

bool	verify_errors(t_sh *sh)
{
	int	x;

	x = 0;
	if (filter_tkerrors(sh) == true)
		return (true);
	if (sh->error.expand_error == true || sh->error.parse_error == true)
	{
		ft_putstr_fd("Minishell: erro de sintaxe junto a símbolo | \
			inesperado: \n", 2);
		g_status = WRONG_SYNTAX;
		return (true);
	}
	else if (sh->error.token_error == true)
	{
		ft_putstr_fd("Minishell: erro de sintaxe junto a símbolo | \
			inesperado: \n", 2);
		g_status = WRONG_SYNTAX;
		return (true);
	}
	else if (sh->vars.cmds_num > 0)
		if (verify_error_helper(sh, x) == true)
			return (true);
	return (false);
}
