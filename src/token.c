
#include "../includes/minishell.h"

static int	count_tokens(t_sh *sh)
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
		if(counter_validation(sh->cmd_line[x - 1]) && sh->cmd_line[x - 1] != 32 && sh->cmd_line[x] == 32)
			counter++;
		x++;
	}
	if(counter_validation(sh->cmd_line[x - 1]) && sh->cmd_line[x - 1] != 32 && sh->cmd_line[x] == '\0')
		counter++;
	//printf("\n\n\n string: %s\n number of tokens: %d\n\n\n", sh.cmd_line, counter);
	
	return(counter);
}


static bool counter_validation(int c)
{
	if(c == 33 || (c >= 35 && c <= 38) ||c >= 40 && c <= 176)
		return(true);
	else 
		return(false);
}

static char *prepare_line(char *str)
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


void	filter_tokens(t_sh *sh)
{
	int	n;

	n = 0;
	while(n < sh->vars.tk_num)
	{
		if(sh->tokens[n].tokens[0] == 34)
		{
			if(!sh->tokens[n].tokens[1])
				sh->tokens[n].f_quote = true;
			else
				sh->tokens[n].d_quote = true;
		}
		else if(sh->tokens[n].tokens[0] == 39)
		{
			if(!sh->tokens[n].tokens[1])
				sh->tokens[n].f_quote = true;
			else
				sh->tokens[n].s_quote = true;
		}
		else if(sh->tokens[n].tokens[0] == 36)
			sh->tokens[n].envp = true;
		else if(sh->tokens[n].tokens[0] == 45)
			sh->tokens[n].arg = true;
		else if(sh->tokens[n].tokens[0] == 124)
			sh->tokens[n].pipe = true;
		else if(sh->tokens[n].tokens[0] == 60)
			sh->tokens[n].r_in = true;
		else if(sh->tokens[n].tokens[0] == 62)
			sh->tokens[n].r_out = true;
		else if(search_ext(sh->tokens[n].tokens))
			sh->tokens[n].file = true;
		else
			sh->tokens[n].cmd = true;
		n++;
	}
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
				printf("\n\nlen = %d\n\nx = %d\n\n", len, x);
				while(sh->cmd_line[x] && sh->cmd_line[x] != ' ')
				{
					len++;
					x++;
				}
				x -= len; 
				printf("\n\nlen = %d\n\nx = %d\n\n", len, x);
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

int main(int ac, char **av, char **envp)
{
   	t_sh	sh;
	
	int x;

	memset(&sh, 0, sizeof(t_sh));
	x = 0;
	sh.envp = envp;
	init_error(&sh);
	while(1)
	{
		sh.vars.tk_num = 0;

		if(sh.cmd_line)
			free(sh.cmd_line);


		
		sh.cmd_line = readline(get_prompt());
		//	printf("\n\nbefore =%s-fim-", sh.cmd_line);

		sh.cmd_line = prepare_line(sh.cmd_line);
		//printf("\n\nafte1111111111111111r line =%s/fim/", sh.cmd_line);

		sh.vars.tk_num = count_tokens(&sh);

		init_tokens(&sh);
		split_cmd(&sh);
		filter_tokens(&sh);
		x = 0;

		
		while(x < sh.vars.tk_num)
		{
			printf("\n aqui esta \n %i \n %s \n", sh.tokens[x].num, sh.tokens[x].tokens);
			x++;
		}


		//get_tokens(&sh);

		//printf("\n\n out of it\n\n tk_num = %d\n cmd_line = %s\n\n\n\n", sh.vars.tk_num, sh.cmd_line);


		free_tokens(&sh);


	}




}


