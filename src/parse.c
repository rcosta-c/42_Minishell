#include "../includes/minishell.h"

/*bool    check_pipe(t_sh *sh)
{
	int x;

	x = 0;
	if (sh->vars.cmds_num > 1)
	{
		while(x < sh->vars.tk_num)
		{
			if(sh->tokens[x].pipe)
				return(false);
			x++;
		}
		return(true);
	}
	return(false);
}*/

bool    check_r_out(t_sh *sh)
{
	int	x;

	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].r_out)
		{
			x++;
			if(sh->tokens[x].file)
				return(false);
			else
				return(true);		
		}
		x++;
	}
	return(false);
}

bool    check_r_in(t_sh *sh)
{
	int	x;

	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].r_in)
		{
			x++;
			if(sh->tokens[x].file)
				return(false);
			else
				return(true);		
		}
		x++;
	}
	return(false);
}

bool    check_before_parse(t_sh *sh)
{
	int x;

	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].f_quote)
			return(true);
		x++;
	}
	return(false);

	//PROCURAR POR MAIS SITUCAOES DE ERRO NO PARSE.
}

/*bool	check_after_parse(t_sh *sh)
{





}*/

void    fill_parser(t_sh *sh)
{
	int x;
	int n_cmd;
	//int narg;

	x = 0;
	n_cmd = 0;
	printf("\n\nENTROUPARSER\n\n");
	while(x < sh->vars.tk_num)
	{
		x = parse_utils(sh, x);
		printf("\nvaibreakar?\n%d\n %d", x, n_cmd);
		if(x == sh->vars.tk_num)
			break;
		//printf("\n %s e num %d \n", sh->tokens[x].tokens, x);
		x = parse_pipes(sh, x, n_cmd);
		n_cmd++;		
	}
}





