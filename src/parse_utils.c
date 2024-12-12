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
		if(x < sh->vars.tk_num && sh->tokens[x + 1].arg == true)
		{
			x++;
			while(sh->tokens[x].arg == true && x < sh->vars.tk_num)
			{
				sh->comands[n_cmd].n_args++;
				x++;
			}
			if(sh->comands[n_cmd].n_args > 0)
				x -= sh->comands[n_cmd].n_args;
			x = parse_with_args(sh, n_cmd, x, narg);		
		}
		else
			x = parse_no_args(sh, n_cmd, x);
	}
	else
		x = parse_no_cmds(sh, n_cmd, x);
	return(x);
}

int		parse_with_args(t_sh *sh, int n_cmd, int x, int narg)
{
	sh->comands[n_cmd].arg = malloc(sizeof(char **) * (sh->comands[n_cmd].n_args + 2));
	sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x - 1].tokens);
	sh->comands[n_cmd].arg[narg++] = ft_strdup(sh->tokens[x - 1].tokens);
	while(narg <= sh->comands[n_cmd].n_args) 
		sh->comands[n_cmd].arg[narg++] = ft_strdup(sh->tokens[x++].tokens);
	if (sh->comands[n_cmd].n_args > 0)
		sh->comands[n_cmd].arg[narg] = NULL;
	else
		sh->comands[n_cmd].arg[1] = NULL;
	if(sh->vars.redir_num > 0)
	{
		x++;
		if(sh->tokens[x - 1].r_in  == true && sh->tokens[x].file == true )
			sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
		else if(sh->tokens[x - 1].r_out == true  && sh->tokens[x].file == true )
			sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
		else if(sh->tokens[x - 1].r_heredoc == true && sh->tokens[x].tokens)
			sh->comands[n_cmd].inheredoc_file = ft_strdup(sh->tokens[x].tokens);
		else if(sh->tokens[x - 1].r_outappend == true && sh->tokens[x].file == true )
			sh->comands[n_cmd].outappendfile = ft_strdup(sh->tokens[x].tokens);
		sh->vars.redir_num--;
		sh->comands[n_cmd].redir = true;
		x++;
	}
	return(x);
}

int		parse_no_args(t_sh *sh, int n_cmd, int x)
{
	sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2); 
	sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[x].tokens); 
	sh->comands[n_cmd].arg[0] = ft_strdup(sh->tokens[x].tokens);
	sh->comands[n_cmd].arg[1] = NULL;
	sh->comands[n_cmd].n_args = 0;
	if(++x < sh->vars.tk_num && (sh->vars.redir_num > 0 || sh->tokens[x].file))
	{
		if(sh->tokens[x].file == true)
			sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x - 1].tokens);
		x++;
		while(sh->tokens[x].pipe == false && x < sh->vars.tk_num)
		{
			if(sh->tokens[x - 1].r_in == true && sh->tokens[x].file)
				sh->comands[n_cmd].infile = ft_strdup(sh->tokens[x].tokens);
			else if(sh->tokens[x - 1].r_heredoc == true && sh->tokens[x].file)
				sh->comands[n_cmd].inheredoc_file = NULL;
			else if(sh->tokens[x - 1].r_out == true && sh->tokens[x].file)
				sh->comands[n_cmd].outfile = ft_strdup(sh->tokens[x].tokens);
			else if(sh->tokens[x - 1].r_outappend == true && sh->tokens[x].file)
				sh->comands[n_cmd].outappendfile = ft_strdup(sh->tokens[x].tokens);
			x++;	
		}
		sh->comands[n_cmd].redir = true;
	}
	return(x);
}

int		parse_no_cmds(t_sh *sh, int n_cmd, int x)
{
	sh->comands[n_cmd].arg = malloc(sizeof(char **) * 2); 
	sh->comands[n_cmd].cmd = ft_strdup(sh->tokens[0].tokens); 
	sh->comands[n_cmd].arg[0] = ft_strdup(sh->tokens[0].tokens);
	sh->comands[n_cmd].arg[1] = NULL;
	x++;
	return(x);
}

int	parse_pipes(t_sh *sh, int z, int n_cmd)
{
	int	x;

	x = z;
	if (sh->vars.pipe_num == 0)
		return (x);

	// Itera até encontrar um pipe ou chegar ao final dos tokens
	while (x < sh->vars.tk_num)
	{
		// Se encontrar um pipe, marca e avança
		if (sh->tokens[x].pipe == true)
		{
			sh->comands[n_cmd].pipes = true; // Marca que este comando usa pipe
			x++; // Avança para o próximo token após o pipe
			break; // Sai do laço, pois encontrou o pipe
		}
		// Caso contrário, pode lidar com redirecionamentos aqui (não implementado)
		// x = parse_redir(sh, x, n_cmd);
		else
		{
			x++;
		}
	}
	return (x);
}