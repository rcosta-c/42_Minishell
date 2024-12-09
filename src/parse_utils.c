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

int	parse_utils(t_sh *sh, int x, int n_cmd)
{
	int	narg;

	narg = 0;
   	if(sh->tokens[x].cmd) 
	{		
		x++;
		if(x < sh->vars.tk_num && sh->tokens[x].arg == true)
		{
			while(sh->tokens[x].arg == true && x < sh->vars.tk_num)
			{
				sh->comands[n_cmd].n_args++;
				x++;
			}
//printf("\n\n (DENTRO)antes X=%d\n", x);
			if(sh->comands[n_cmd].n_args > 0)
			{
				x -= sh->comands[n_cmd].n_args;
			}
//printf("\nnargs=%d\nagora o X =%d", sh->comands[n_cmd].n_args, x);
//printf("\n\n (DENTRO)depois X=%d\n", x);
				sh->comands[n_cmd].arg = malloc(sizeof(char **) * (sh->comands[n_cmd].n_args + 2));
//sh->comands[n_cmd].arg[narg - 1] = ft_strdup(sh->tokens[x].tokens);
//printf("\n\ncomandovaiser %s\n", sh->comands[n_cmd].cmd);
//printf("arg1=%s ", sh->tokens[x].tokens);			
//printf("\ncmd vai ser =%s\n", sh->tokens[x - 1].tokens);
				sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x - 1].tokens);
				sh->comands[n_cmd].arg[narg] = ft_strdup(sh->tokens[x - 1].tokens);
				narg++; 
				while(narg <= sh->comands[n_cmd].n_args) 
				{
					sh->comands[n_cmd].arg[narg] = ft_strdup(sh->tokens[x].tokens);
//printf("\narg %d = %s", narg, sh->comands[n_cmd].arg[narg]);				
				
					narg++;
					x++;
				}
//printf("\narg %d = %s\n e narg=%d", narg, sh->comands[n_cmd].arg[narg - 1], narg);				

//printf("\n\ncmd=%s\narg[0]=%s\narg1=%s", sh->comands[n_cmd].cmd, sh->comands[n_cmd].arg[0], sh->comands[n_cmd].arg[1]);
				if (sh->comands[n_cmd].n_args > 0)
				{
					sh->comands[n_cmd].arg[narg] = NULL;

				}
				else
					sh->comands[n_cmd].arg[1] = NULL;


//printf("\nonde ja vai %s \n\n\n", sh->tokens[x - 1].tokens);
//printf("111\n%s\n", sh->tokens[x].tokens);
//printf("if redir entao vai\narg %d = %s", narg, sh->comands[n_cmd].arg[narg]);				
			if(sh->vars.redir_num > 0)
			{

				x++;
//printf("222\n%s\n", sh->tokens[x].tokens);
				if(sh->tokens[x - 1].r_in  == true && sh->tokens[x].file == true )
					sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
				else if(sh->tokens[x - 1].r_out == true  && sh->tokens[x].file == true )
					sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
				else if(sh->tokens[x - 1].r_heredoc == true && sh->tokens[x].tokens)
				{
					printf("\n\n entrou onde queriamos redir heredoc\n\n");	
					sh->comands[n_cmd].inheredoc_file = ft_strdup(sh->tokens[x].tokens);

				}
				else if(sh->tokens[x - 1].r_outappend == true && sh->tokens[x].file == true )
					sh->comands[n_cmd].outappendfile = ft_strdup(sh->tokens[x].tokens);
				sh->vars.redir_num--;
//printf("\n\n\vai altarar o redir bool esta em %dn\n", sh->comands[n_cmd].redir);
				sh->comands[n_cmd].redir = true;
//printf("\n\n\vai ja alterou o redir bool esta em %dn\n", sh->comands[n_cmd].redir);
				x++;
			}
//printf("x=%d\n", x);
			return(x);

		}
		else
		{	
			sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2); 
			sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x - 1].tokens); 
			sh->comands[n_cmd].arg[0] = ft_strdup(sh->tokens[x - 1].tokens);
			sh->comands[n_cmd].arg[1] = NULL;
			if(x < sh->vars.tk_num && (sh->vars.redir_num > 0 || sh->tokens[x].file))
			{
				if(sh->tokens[x].file == true)
					sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x - 1].tokens);
				x++;
//				printf("\n\nestou aqui\ntoken[x]=%d\n", x);
				while(sh->tokens[x].pipe == false && x < sh->vars.tk_num)
				{
					if(sh->tokens[x - 1].r_in == true && sh->tokens[x].file)
						sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
					else if(sh->tokens[x - 1].r_heredoc == true && sh->tokens[x].file)
						sh->comands[n_cmd].inheredoc_file = NULL;//ft_strdup(sh->tokens[x].tokens);
					else if(sh->tokens[x - 1].r_out == true && sh->tokens[x].file)
						sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
					else if(sh->tokens[x - 1].r_outappend == true && sh->tokens[x].file)
						sh->comands[n_cmd].outappendfile = ft_strdup(sh->tokens[x].tokens);
					x++;	
				}
				//if(sh->vars.redir_num  > 0)
				//	sh->vars.redir_num--;
				sh->comands[n_cmd].redir = true;

			}
			
	//		printf("\n\nsaaaaaou aqui\n\n");
			return(sh->vars.tk_num);
		}

	}
	return(x);
}
/*
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
	
}*/
	 
int		parse_pipes(t_sh *sh, int z, int n_cmd)
{
	int x;

	x = z;
	if(sh->vars.pipe_num == 0)
		return(x);
	x++;
	//while(sh->tokens[x].pipe == false && (x < sh->vars.tk_num))
	//	x = parse_redir(sh, x, n_cmd);
	if(sh->tokens[x].pipe == true && (x < sh->vars.tk_num))
	{
		sh->comands[n_cmd].pipe = true;
		x++;
	}
	return(x);
}

