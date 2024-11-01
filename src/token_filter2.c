#include "../includes/minishell.h"

void	filter_file (t_sh *sh, int n)
{
	int	x;

	x = ft_strlen(sh->tokens[n].tokens) - 5;
	while(sh->tokens[n].tokens[x])
	{
		if(sh->tokens[n].tokens[x] == '.')
		{
			sh->tokens[n].file = true;
			break;
		}
		x++;
	}
}

void	filter_pipes_redir(t_sh *sh, int n)
{
	int	x;
	if(sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false)
	{
		if(sh->tokens[n].tokens[0] == '|')
			sh->tokens[n].pipe = true;
		if(sh->tokens[n].tokens[0] == '<')
			sh->tokens[n].r_in = true;		//Verificar se esta correcto
		if(sh->tokens[n].tokens[0] == '>')
			sh->tokens[n].r_out = true;		//Verificar se esta correcto
	}
}

void	filter_quotes(t_sh *sh, int n)
{
	int x;

	if(sh->tokens[n].tokens[0] == 34)
	{
		x = 1;
		while(sh->tokens[n].tokens[x])
		{
			if(sh->tokens[n].tokens[x] == '$')
				sh->tokens[n].exp_e = true;
			x++;
		}
		if(sh->tokens[n].tokens[x - 1] == 34)
			sh->tokens[n].d_quote = true;
		else
		{
			sh->tokens[n].f_quote = true;
			sh->tokens[n].exp_e = false;
		}
	}
	if(sh->tokens[n].tokens[0] == 39)
	{
		if(sh->tokens[n].tokens[ft_strlen(sh->tokens[n].tokens) - 1] == 39)
			sh->tokens[n].s_quote = true;
		else
			sh->tokens[n].f_quote = true;
	}
}
