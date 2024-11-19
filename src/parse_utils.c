#include "../includes/minishell.h"

int	parse_utils(t_sh *sh, int z)
{
	int x;
	int	narg;
	int	n_cmd;

	narg = 0;
	n_cmd = 0;
	x = z;
   	if(sh->tokens[x].cmd)
	{
		x++;
		while(sh->tokens[x].arg)// && (*x < sh->vars.tk_num))
		{
			sh->comands[n_cmd].n_args++;
			x++;
		}
		x -= sh->comands[n_cmd].n_args + 1;
		sh->comands[n_cmd].arg = malloc(sizeof(char **) * (sh->comands[n_cmd].n_args + 2));
		sh->comands[n_cmd].arg[narg] = ft_strdup(sh->tokens[x].tokens);
		sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x++].tokens); //APAGAR ESTE AQUI
		narg++;
		while(sh->tokens[x].arg)
			sh->comands[n_cmd].arg[narg++] = ft_strdup(sh->tokens[x++].tokens);
		sh->comands[n_cmd].arg[narg] = NULL;
	}
	return(x);
}

int	parse_pipes(t_sh *sh, int z, int n_cmd)
{
	int x;

	x = z;
	while(sh->tokens[x].pipe == false && (x < sh->vars.tk_num))
	{
		if(sh->tokens[x].r_out)// && sh->tokens[x + 1].file)
		{
			x++;
			sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
			x++;
		}
		if(sh->tokens[x].r_in)// && sh->tokens[x + 1].file)
		{
			x++;
			sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
			x++;
		}
	//printf("\n %s \n", sh->tokens[x].tokens);
	}
	if(sh->tokens[x].pipe == true && (x < sh->vars.tk_num))
	{
		sh->comands[n_cmd].pipe = true;
		x++;
	}
	return(x);
}





