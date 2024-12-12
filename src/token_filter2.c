#include "../includes/minishell.h"

void	filter_file(t_sh *sh, int n)
{
	int	x;

	x = 0;
	while(sh->tokens[n].tokens[x])
	{
		if(sh->tokens[n].tokens[x] == '.')
		{
			if(sh->tokens[n].tokens[x + 1] == '.')
				break;
			sh->tokens[n].file = true;
			break;
		}
		x++;
	}
	if(n > 0 && sh->tokens[n - 1].r_heredoc == true)
	{
		sh->tokens[n].file = true;
		sh->tokens[n].arg = false;
	}
}

void	filter_pipes_redir(t_sh *sh, int n)
{
	if(sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false)
	{
		if(sh->tokens[n].tokens[0] == '|')
			{
				sh->tokens[n].pipe = true;
				sh->vars.pipe_num++;
			}
		if(sh->tokens[n].tokens[0] == '<')
		{
			if(!sh->tokens[n].tokens[1])
			{
				sh->tokens[n].r_in = true;
				sh->vars.redir_num++;
			}
			if(sh->tokens[n].tokens[1] == '<')
			{
				sh->tokens[n].r_heredoc = true;
				sh->vars.redir_num++;
				sh->vars.heredoc_num++;
			}
		}
		if(sh->tokens[n].tokens[0] == '>')
		{
			if(!sh->tokens[n].tokens[1])
			{
				sh->tokens[n].r_out = true;
				sh->vars.redir_num++;
			}
			if(sh->tokens[n].tokens[1] == '>')
			{
				sh->tokens[n].r_outappend = true;
				sh->vars.redir_num++;
			}
		}
	}
}


void	filter_quotes(t_sh *sh, int n, int x)
{
	int len;

	len = ft_strlen(sh->tokens[n].tokens);
	if(sh->tokens[n].tokens[0] == 34)
	{
		while(sh->tokens[n].tokens[x++])
			if(sh->tokens[n].tokens[x] == '$')
				sh->tokens[n].exp_e = true;
		if(sh->tokens[n].tokens[len - 1] == 34 && len > 1)
			sh->tokens[n].d_quote = true;
		else
			sh->tokens[n].f_quote = true;
	}
	else if(sh->tokens[n].tokens[0] == 39)
	{
		if(sh->tokens[n].tokens[len - 1] == 39 && len > 1)
			sh->tokens[n].s_quote = true;
		else
			sh->tokens[n].f_quote = true;
	}
}
