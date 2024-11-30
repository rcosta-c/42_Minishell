#include "../includes/minishell.h"

static char	*clean_quote(char *str)
{
	int		len;
	int		x;
	int		xx;
	char	*dest;

	x = 1;
	xx = 0;
	len = ft_strlen(str);
	dest = malloc(sizeof(char *) * len - 1);
	while(str[x])
	{
		if(len - 1 == x)
			break;
		dest[xx] = str[x];
		x++;
		xx++;
	}
	dest[xx] = '\0';
	free(str);
	return(dest);
}

void	remove_quoted(t_sh *sh)
{
	int	x;

	if(sh->vars.tk_num == 0)
		return;
	x = 0;
	while(x < sh->vars.tk_num)
	{
		if(sh->tokens[x].d_quote)
		{
			sh->tokens[x].tokens = clean_quote(sh->tokens[x].tokens);
		}
		if(sh->tokens[x].s_quote)
		{
			sh->tokens[x].tokens = clean_quote(sh->tokens[x].tokens);
		}
		x++;
	}
}

int	parse_utils(t_sh *sh, int z)
{
	int x;
	int	narg;
	int	n_cmd;

	narg = 1;
	n_cmd = 0;
	x = z;
   	if(sh->tokens[x].cmd)
	{
		x++;
		if(x < sh->vars.tk_num && sh->tokens[x].arg == true)
		{
			while(x < sh->vars.tk_num)
			{
				sh->comands[n_cmd].n_args++;
				x++;
			}
//			printf("\n\n (DENTRO)antes X=%d\n", x);

			x -= sh->comands[n_cmd].n_args + 1;
//						printf("\n\n (DENTRO)depois X=%d\n", x);

			sh->comands[n_cmd].arg = malloc(sizeof(char **) * (sh->comands[n_cmd].n_args + 2));
			sh->comands[n_cmd].arg[narg - 1] = ft_strdup(sh->tokens[x].tokens);
			sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x++].tokens); 
			while(narg <= sh->comands[n_cmd].n_args)
				sh->comands[n_cmd].arg[narg++] = ft_strdup(sh->tokens[x++].tokens);
			sh->comands[n_cmd].arg[narg] = NULL;
		}
		else
		{			//printf("\n sem verificar argumentos\n");

			sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2);
			sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x - 1].tokens); 
			sh->comands[n_cmd].arg[0] = ft_strdup(sh->tokens[x - 1].tokens);
			sh->comands[n_cmd].arg[1] = NULL;
		}
	}
	return(x);
}

static int parse_redir(t_sh *sh, int x, int n_cmd)
{
	if(sh->tokens[x].r_out)// && sh->tokens[x + 1].file)
	{
		x++;
		sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
		x++;
	}
	if(sh->tokens[x].r_outappend)// && sh->tokens[x + 1].file)
	{
		x++;
		sh->comands[n_cmd].outappendfile = ft_strdup(sh->tokens[x].tokens);
		x++;
	}
	if(sh->tokens[x].r_in)// && sh->tokens[x + 1].file)
	{
		x++;
		sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
		x++;
	}
	else
		x++;
	return(x);
}

int	parse_pipes(t_sh *sh, int z, int n_cmd)
{
	int x;

	x = z;
	if(sh->vars.pipe_num == 0)
		return(x);
	while(sh->tokens[x].pipe == false && (x < sh->vars.tk_num))
		x = parse_redir(sh, x, n_cmd);
	if(sh->tokens[x].pipe == true && (x < sh->vars.tk_num))
	{
		sh->comands[n_cmd].pipe = true;
		x++;
	}
	return(x);
}

