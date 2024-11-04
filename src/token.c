
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




