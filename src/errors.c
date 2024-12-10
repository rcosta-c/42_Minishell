#include "../includes/minishell.h"

static void	filter_tkerrors(t_sh *sh)
{
	int	x;

	x = 0;
//printf("\nfilter_tkerrors-sh_status=%d\n", sh->vars.sh_status);
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[0].pipe == true)
		{
			g_status = 2;
			sh->vars.sh_status = false;
			return;
		}
		if(sh->tokens[sh->vars.tk_num - 1].pipe == true)
		{
			g_status = WRONG_SYNTAX;
			sh->vars.sh_status = false;
			return;
		}
		if(sh->tokens[x].r_heredoc || sh->tokens[x].r_in || sh->tokens[x].r_out || sh->tokens[x].r_outappend)
		{
			x++;
			if(sh->tokens[x].file == false)
			{
				g_status = WRONG_SYNTAX;
				sh->vars.sh_status = false;
				return;
			}
		}
		if(sh->tokens[x].pipe)
		{
			x++;
			if(sh->tokens[x].cmd == false)
			{
				g_status = WRONG_SYNTAX;
				sh->error.token_error = true;
				sh->vars.sh_status = false;
				return;
			}
		}
		x++;
	}
	return;
}

bool    verify_errors(t_sh *sh)
{
	int x;

	x = 0;
	filter_tkerrors(sh);
	if(sh->error.expand_error == true || sh->error.parse_error == true)
	{
		ft_putstr_fd("Minishell: erro de sintaxe junto a símbolo | inesperado: ", 2);
		g_status = WRONG_SYNTAX;
		return(true);
	}
	else if(sh->error.token_error == true)
	{
		ft_putstr_fd("Minishell: erro de sintaxe junto a símbolo | inesperado: ", 2);
		g_status = WRONG_SYNTAX;
		return(true);
	}
	else  if(sh->vars.cmds_num > 0)
	{
		while(x < sh->vars.cmds_num)
		{
			if(sh->comands[x].errors.empty_pipe == true)
			{
				ft_putstr_fd("syntax error near unexpected token '|'", 2);
				g_status = WRONG_SYNTAX;
				return(true);
			}
			else if(sh->comands[x].errors.infile_noaccess == true || sh->comands[x].errors.infile_notvalid == true)
			{
				ft_putstr_fd("< : Permissão recusada: ", 2);

				g_status = NO_PERMISSION;
				return(true);
			}			
			else if(sh->comands[x].errors.outfile_noaccess == true || sh->comands[x].errors.outfile_notvalid == true)
			{
				ft_putstr_fd("> : Permissão recusada: ", 2);
				g_status = NO_PERMISSION;
				return(true);
			}
			else
				x++;
		}	
	}
	return(false);
}