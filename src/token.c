
#include "../includes/minishell.h"

int	count_tokens(t_sh *sh)
{
	int	x;
	int	counter;

	x = 0;
	counter = 0;
	while(sh->cmd_line[x])
	{
		if(sh->cmd_line[x] == 34 || sh->cmd_line[x] == 39)
		{
			x = check_type_quote(sh->cmd_line, x);
			counter++;
		}		
		else if(counter_validation(sh->cmd_line[x - 1]) && sh->cmd_line[x - 1] != 32 && sh->cmd_line[x] == 32)
			counter++;
		x++;
	}
	if(counter_validation(sh->cmd_line[x - 1]) && sh->cmd_line[x - 1] != 32 && sh->cmd_line[x] == '\0')
		counter++;
	//printf("\n\n\n string: %s\n number of tokens: %d\n\n\n", sh.cmd_line, counter);
	
	return(counter);
}


bool counter_validation(int c)
{
	if(c == 33 || (c >= 35 && c <= 38) ||c >= 40 && c <= 176)
		return(true);
	else 
		return(false);
}

char *prepare_line(char *str)
{
	int     x_o;
	int     x_d;
	char    temp[1000];
	char    *dest;

	x_o = 0;
	x_d = 0;
	while(str[x_o])
	{
		if(str[x_o] == 34)
		{
			if(check_if_dquote(str, x_o) || check_if_squote(str, x_o))
			{
				temp[x_d++] = str[x_o++];
				while(str[x_o] != 34)
					temp[x_d++] = str[x_o++];
			}
			else
				temp[x_d++] = str[x_o++];	
			

		}
		while(token_is_valid(&str[x_o]))
			temp[x_d++] = str[x_o++];
		if(str[x_o] == 32)
		{
			while(str[x_o] == 32)
				x_o++;
			if(str[x_o] != '\0' && x_d > 0)
				temp[x_d++] = 32;
		}
	}
	temp[x_d] = '\0';
	dest = ft_strdup(temp);
	return(dest);
}

void	split_cmd(t_sh *sh)
{
	int	len;
	int x;
	int xx;
	int n;

	n = 0;
	x = 0;
	if(sh->vars.tk_num == 0)
		exit;
	if(sh->vars.tk_num == 1)
	{
		len = ft_strlen(sh->cmd_line);
		sh->tokens[0].tokens = malloc(sizeof(char *) * (len + 1));
		while(x < len)
		{
					sh->tokens[0].tokens[x] = sh->cmd_line[x];
					x++;
		}
		sh->tokens[0].tokens[x] = '\0';
	}
	else
	{
		while(1)
		{
			xx = 0;
			len = 0;
			if(!sh->cmd_line[x])
				break;
			else if(check_if_squote(sh->cmd_line, x) || check_if_dquote(sh->cmd_line, x))
			{
				len = check_type_quote(sh->cmd_line, x) - x;
				sh->tokens[n].tokens = malloc(sizeof(char *) * (len + 1));
				while(xx < len)
				{
					sh->tokens[n].tokens[xx] = sh->cmd_line[x];
					x++;
					xx++;
				}
				sh->tokens[n].tokens[xx] = '\0';
				n++;
			}
			else
			{
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
				n++;
			}	
		x++;  
		}
	}
}



