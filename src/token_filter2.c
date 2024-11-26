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
			{
				sh->tokens[n].pipe = true;
				sh->vars.pipe_num++;
			}
		if(sh->tokens[n].tokens[0] == '<')
		{
			sh->tokens[n].r_in = true;
			sh->vars.redir_num++;
		}
		if(sh->tokens[n].tokens[0] == '>')
		{
			if(!sh->tokens[n].tokens[1])
				sh->tokens[n].r_out = true;		
			if(sh->tokens[n].tokens[1] == '>')
				sh->tokens[n].r_outappend = true;
			sh->vars.redir_num++;
		}
	}
}

void	filter_quotes(t_sh *sh, int n)
{
	int x;

	x = 1;
	if(sh->tokens[n].tokens[0] == 34)
	{
		while(sh->tokens[n].tokens[x])
		{
			if(sh->tokens[n].tokens[x] == '$')
				sh->tokens[n].exp_e = true;
			x++;
		}
		if(sh->tokens[n].tokens[x - 1] == 34 && x > 1)
			sh->tokens[n].d_quote = true;
		else
		{
			sh->tokens[n].f_quote = true;
			sh->tokens[n].exp_e = false;
		}
	}
	if(sh->tokens[n].tokens[0] == 39)
	{
		x = ft_strlen(sh->tokens[n].tokens) - 1;
		if(sh->tokens[n].tokens[x] == 39 && x > 1)
			sh->tokens[n].s_quote = true;
		else
			sh->tokens[n].f_quote = true;
	}
}
