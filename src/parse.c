#include "../includes/minishell.h"

bool    check_before_parse(t_sh *sh)
{
	int x;

	x = 0;


	//FALTA VERIFICAR SE EXISTE MAIS DE 1 COMANDO , TEM DE HAVER PIPE. SE NAO HOUVER EMITIR ERRO.
	

	//PROCURAR POR MAIS SITUCAOES DE ERRO NO PARSE.

	//VERIFICAR SE OS R_IN E R_OUT TEM FILE DENTRO.
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].f_quote)
			return(true);
		x++;
	}
	return(false);
}


/*
-procura flags de comando

*/
void    fill_parser(t_sh *sh)
{
	int x;
	int n_cmd;
	int narg;

	x = 0;
	n_cmd = 0;
	while(x < sh->vars.tk_num)
	{
		narg = 0;
		//printf("\n\n aqui quia = %s\n\n", sh->tokens[x].tokens);
		if(sh->tokens[x].cmd)
		{
			sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x].tokens);
			x++;
			while(sh->tokens[x].arg && (x < sh->vars.tk_num))
			{
				sh->comands[n_cmd].n_args++;
				x++;
			}
			//printf("acabou de contar   %d \n", sh->comands[n_cmd].n_args);
			if(sh->comands[n_cmd].n_args > 0)
			{
				sh->comands[n_cmd].arg = malloc(sizeof(char **) * (sh->comands[n_cmd].n_args + 1));
				x -= sh->comands[n_cmd].n_args;
				while(sh->tokens[x].arg)
				{
					
					sh->comands[n_cmd].arg[narg] = ft_strdup(sh->tokens[x].tokens);
					//printf("\ncmd num=%d \n %s \n", n_cmd, sh->comands[n_cmd].arg[narg]);
					x++;
					narg++;
				}
				sh->comands[n_cmd].arg[narg] = '\0';
			}
			//printf("passo aqui\n");
		}
		if(x == sh->vars.tk_num)
			break;
		//printf("\n %s e num %d \n", sh->tokens[x].tokens, x);
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
		n_cmd++;		

	}
}
