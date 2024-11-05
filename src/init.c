#include "../includes/minishell.h"

void	init_error(t_sh *sh)
{
	sh->error.cmd_error = false;
	sh->error.token_error = false;
	sh->error.expand_error = false;
	sh->error.parse_error = false;
	sh->error.exec_error = false;
}


void	init_tokens(t_sh *sh)
{
	int x;
	char	**temp;

	if(sh->vars.tk_num == 0)
		return;
	x = 0;
	sh->tokens = malloc(sizeof(t_tokens) * (sh->vars.tk_num + 1));
	if(!sh->tokens)
		exit(EXIT_FAILURE);
	while(x < sh->vars.tk_num)
	{
		sh->tokens[x].num = x;
		sh->tokens[x].cmd = false;
		sh->tokens[x].arg = false;
		sh->tokens[x].pipe = false;
		sh->tokens[x].r_in = false;
		sh->tokens[x].r_out = false;
		sh->tokens[x].s_quote = false;
		sh->tokens[x].d_quote = false;
		sh->tokens[x].f_quote = false;
		sh->tokens[x].envp = false;
		sh->tokens[x].file = false;
		sh->tokens[x].exp_e = false;
		sh->tokens[x].exp_t = false;
		x++;
	}
}

void	init_parser(t_sh *sh)
{
	int	x;
	int	n_args;

	x = 0;
	sh->comands = malloc(sizeof(t_exec) * (sh->vars.cmds_num + 1));
	if(!sh->comands)
		exit(EXIT_FAILURE);
	while(x < sh->vars.cmds_num)
	{
		sh->comands[x].pipe = false;
		sh->comands[x].infile = NULL;
		sh->comands[x].outfile = NULL;
		sh->comands[x].arg = NULL;
		sh->comands[x].n_args = 0;
		x++;
	}
		// CONTAR ARGUMENTO DE CADA COMANDO PARA ALOCAR MEMORIA
	/*while(x < sh->vars.tk_num)
	{
		n_args = 0;
		if(sh->tokens[x].cmd)
		{
			x++;
			while(!sh->tokens[x].pipe && x < sh->vars.tk_num)
			{
				n_args++;
			}
			if(n_args == 0)
				break;
			else
			{
				sh->comands[]
			}

		}
		x++;
	}*/
}