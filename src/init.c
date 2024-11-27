#include "../includes/minishell.h"

void	init_error(t_sh *sh)
{
	sh->vars.redir_num = 0;
	sh->error.cmd_error = false;
	sh->error.token_error = false;
	sh->error.expand_error = false;
	sh->error.parse_error = false;
	sh->error.exec_error = false;
}


void	init_tokens(t_sh *sh)
{
	int x;

	if(sh->vars.tk_num == 0)
		return;
	x = 0;
	sh->tokens = malloc(sizeof(t_tokens) * (sh->vars.tk_num + 1));
	if(!sh->tokens)
		exit(EXIT_FAILURE);
	while(x < sh->vars.tk_num)
	{
		sh->tokens[x].num = x;
		init_tk_flag1(sh, x);
		x++;
	}
}

void	init_parser(t_sh *sh)
{
	int	x;

	x = 0;
	sh->comands = malloc(sizeof(t_exec) * (sh->vars.cmds_num + 1));
	if(!sh->comands)
		exit(EXIT_FAILURE);
	while(x < sh->vars.cmds_num)
	{
		init_cmds(sh, x);
		x++;
	}
}