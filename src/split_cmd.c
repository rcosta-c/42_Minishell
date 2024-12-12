#include "../includes/minishell.h"

static int    split_quote(t_sh *sh, int x, int n)
{
    int len;
    int xx;

    xx = 0;    
    len = check_type_quote(sh->cmd_line, x) - x;
	sh->tokens[n].tokens = malloc(sizeof(char *) * (len + 1));
	while(xx < len)
	{
		sh->tokens[n].tokens[xx] = sh->cmd_line[x];
		x++;
		xx++;
    }
	sh->tokens[n].tokens[xx] = '\0';
    return(x);
}

static int  split_cicle(t_sh *sh, int x, int n)
{
    int xx;
    int len;

    xx = 0;
	len = 0;
    while(sh->cmd_line[x] && sh->cmd_line[x] != ' ')
	{
		len++;
		x++;
	}
	x -= len; 
	sh->tokens[n].tokens = malloc(sizeof(char *) * (len + 1));
	while(sh->cmd_line[x] && sh->cmd_line[x] != ' ')
	{
		sh->tokens[n].tokens[xx] = sh->cmd_line[x];
		xx++;
		x++;
	}
	sh->tokens[n].tokens[xx] = '\0';
    return(x);
}

void	split_cmd(t_sh *sh)
{
	int x;
	int n;

	n = 0;
	x = 0;
	if(sh->vars.sh_status == false)
		return;
	if(sh->vars.tk_num == 0)
		return;
	while(1)
	{
		if(!sh->cmd_line[x])
			break;
		else if(check_if_squote(sh->cmd_line, x) || check_if_dquote(sh->cmd_line, x))
            x = split_quote(sh, x, n++);
		else
              x = split_cicle(sh, x, n++);
	    if(!sh->cmd_line[x])
			break;
		x++;  
	}
}


