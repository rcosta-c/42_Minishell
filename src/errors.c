/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:30 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/21 02:19:37 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



bool filter_cmd_error(t_sh *sh)
{
    int x;
    struct stat path_stat;

    x = 0;
    if (sh->vars.sh_status == false)
        return (true);
    while (x < sh->vars.cmds_num)
    {
        if (stat(sh->comands[x].cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
        {
            fprintf(stderr, " Is a directory\n");
            g_status = NO_PERMISSION;
            return (true);
        }
        if (!access(sh->comands[x].cmd, F_OK))
        {
			//printf("\n\nPAASSEEII AQUI\n\n");
            if (access(sh->comands[x].cmd, X_OK))
            {
                fprintf(stderr, "Permission denied: %s\n", sh->comands[x].cmd);
                g_status = NO_PERMISSION;
                return (true);
            }
        }
        else
        {
            sh->comands[x].errors.cmd_not_found = true;
            fprintf(stderr, " command not found\n");
            g_status = CMD_NOT_FOUND;
            return (true);
        }
        if (sh->comands[x].cmd[0] == '$') 
        {
            char *env_var = getenv(&sh->comands[x].cmd[1]);
            if (!env_var || !*env_var)
            {
                fprintf(stderr, "Minishell: variável de ambiente não resolvida: %s\n", sh->comands[x].cmd);
                g_status = ENV_VAR_NOT_FOUND;
                return (true);
            }
        }

        x++;
    }
    return (false);
}

/*
bool	filter_cmd_error(t_sh *sh)
{
	int x;

	x = 0;
	if(sh->vars.sh_status == false)
		return(true);
	while(x < sh->vars.cmds_num)
	{
		if (!access(sh->comands[x].cmd, F_OK)) // Comando existe
		{
			if (access(sh->comands[x].cmd, X_OK)) // Sem permissão
			{
				fprintf(stderr, "Minishell: permissão negada: %s\n", sh->comands[x].cmd);
				g_status = NO_PERMISSION;
				return(true);
			}
		}
		else
		{
			sh->comands[x].errors.cmd_not_found = true;
			fprintf(stderr, "Minishell: comando não encontrado: %s\n", sh->comands[x].cmd);
			g_status = CMD_NOT_FOUND;
			return(true);
		}
		x++;
	}
	return(false);
}*/
static bool	filter_tkerrors2(t_sh *sh)
{
	if(sh->tokens[0].r_heredoc || sh->tokens[0].r_in || 
			sh->tokens[0].r_out || sh->tokens[0].r_outappend)
	{
		ft_putstr_fd(" syntax error near unexpected token `newline'\n", 2);
		g_status = SYNTAX_MISPELL;
		sh->vars.sh_status = false;
		return (true);
	}
	else if(sh->tokens[sh->vars.tk_num - 1].r_heredoc || 
			sh->tokens[sh->vars.tk_num - 1].r_in || 
			sh->tokens[sh->vars.tk_num - 1].r_out || 
			sh->tokens[sh->vars.tk_num - 1].r_outappend)
	{
		ft_putstr_fd(" syntax error near unexpected token `newline'\n", 2);
		g_status = SYNTAX_MISPELL;
		sh->vars.sh_status = false;
		return (true);
	}
	return(false);	
}

static bool	filter_tkerrors(t_sh *sh)
{
	if(sh->vars.tk_num == sh->vars.pipe_num || 
		sh->tokens[0].pipe == true)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		g_status = SYNTAX_MISPELL;
		sh->vars.sh_status = false;
		return (true);
	}
	else if(sh->tokens[sh->vars.tk_num - 1].pipe == true)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		g_status = SYNTAX_MISPELL;
		sh->vars.sh_status = false;
		return (true);
	}
	else
		filter_tkerrors2(sh);
	return(false);
}

static bool	verify_error_helper(t_sh *sh, int x)
{
	while(x < sh->vars.cmds_num)
	{
		if(sh->comands[x].errors.empty_pipe == true)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			g_status = SYNTAX_MISPELL;
			return(true);
		}
		else if(sh->comands[x].errors.infile_noaccess == true || sh->comands[x].errors.infile_notvalid == true)
		{
			ft_putstr_fd("< : Permissão recusada: \n", 2);
			g_status = NO_PERMISSION;
			return(true);
		}			
		else if(sh->comands[x].errors.outfile_noaccess == true || sh->comands[x].errors.outfile_notvalid == true)
		{
			ft_putstr_fd("> : Permissão recusada: \n", 2);
			g_status = NO_PERMISSION;
			return(true);
		}
		else if (sh->comands[x].errors.empty_redir == true)
		{
			ft_putstr_fd("EMPTY REDIR - syntax error near unexpected token `|'\n", 2);
			g_status = SYNTAX_MISPELL;
			return(true);			
		}
		else
			x++;
	}
	return(false);
}

bool    verify_errors(t_sh *sh)
{
	int x;

	x = 0;
	if(filter_tkerrors(sh) == true)
		return(true);
	if(sh->error.expand_error == true || sh->error.parse_error == true)
	{
		ft_putstr_fd("Minishell: erro de sintaxe junto a símbolo | inesperado: \n", 2);
		g_status = WRONG_SYNTAX;
		return(true);
	}
	else if(sh->error.token_error == true)
	{
		ft_putstr_fd("Minishell: erro de sintaxe junto a símbolo | inesperado: \n", 2);
		g_status = WRONG_SYNTAX;
		return(true);
	}
	else  if(sh->vars.cmds_num > 0)
		if(verify_error_helper(sh, x) == true)
			return(true);
	return(false);
}

