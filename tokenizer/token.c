#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../includes/minishell.h"

static bool	check_if_squote(char *str, int x_o);
static bool	check_if_dquote(char *str, int x_o);
static char *prepare_line(char *str);
static char	*ft_2strdup(const char *s);
static int	count_tokens(t_sh *sh);
static int	check_squote(char *str, int counter);
static int	check_dquote(char *str, int counter);
static bool counter_validation(int c);
static void	tokens_2_matrix(t_sh *sh);
static void	init_tokens(t_sh *sh);


static int	check_dquote(char *str, int counter)
{
	int 	temp;

	temp = counter;
	if(str[temp] == 34)
	{
		temp++;
		while(str[temp] && str[temp] != 34)
			temp++;
		if(str[temp] == '\0')
			return(counter);
		else
		{
			temp++;
			return(temp);
		}
	}
	return(counter);
	
}

static int	check_squote(char *str, int counter)
{
	int 	temp;

	temp = counter;
	if(str[temp] == 39)
	{
		temp++;
		while(str[temp] && str[temp] != 39)
			temp++;
		if(str[temp] == '\0')
			return(counter);
		else
		{
			temp++;
			return(temp);
		}
	}
	return(counter);
	
}

static int check_type_quote(char *cmd_line, int x)
{
	if(cmd_line[x] == 34)
	{
		return(check_dquote(cmd_line, x));
	}
	else if(cmd_line[x] == 39)
	{
		return(check_squote(cmd_line, x));
	}
	else
		return(x);
}

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

static bool token_is_valid(char *src)
{
	if(*src == 33 || *src >= 35 && *src <= 126)
		return(true);
	else if(*src == 9)
		return(true);
	else
		return(false);
}

static char	*ft_2strdup(const char *s)
{
	unsigned int	cnt;
	char			*dest;

	cnt = 0;
	while (s[cnt] != '\0')
		cnt++;
	dest = (char *)malloc(sizeof(char) * cnt + 1);
	if (!dest)
		return (NULL);
	cnt = 0;
	while (s[cnt] != '\0')
	{
		dest[cnt] = s[cnt];
		cnt++;
	}
	dest[cnt] = '\0';
	return (dest);
}

static bool	check_if_dquote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	while(str[x])
	{
		if(str[x] == 34)
			counter++;
		x++;
	}
	if(counter % 2 != 0)
		return(true);
	else
		return(false);
}

static bool	check_if_squote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	while(str[x])
	{
		if(str[x] == 39)
			counter++;
		x++;
	}
	if(counter % 2 != 0)
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
	dest = ft_2strdup(temp);
	return(dest);
}
/*
void	tokens_2_matrix(t_sh *sh)
{
	int	x;

	x = 0;
	while(x <= )




}*/


/*
void    get_tokens(t_sh *sh)
{
	
	//memset(&sh.tokens, 0, sizeof(t_tokens));
	
	//printf("\n\n2222222222\n\n");

	sh->vars.tk_num = count_tokens(sh);

	
	init_tokens(sh);
	//tokens_2_matrix(sh);

	printf("\n\n  ja esta   \n\n ");
	
	

	//printf("\n\n the string \n %s \n\n", sh->cmd_line);







}*/


static void	init_tokens(t_sh *sh)
{
	int x;

	x = 0;
	sh->tokens = malloc(sizeof(t_tokens) * (sh->vars.tk_num));
	if(!sh->tokens)
		exit(EXIT_FAILURE);
	while(x < sh->vars.tk_num)
	{
		sh->tokens[x].cmd = false;
		sh->tokens[x].arg = false;
		sh->tokens[x].pipe = false;
		sh->tokens[x].r_in = false;
		sh->tokens[x].r_out = false;
		sh->tokens[x].s_quote = false;
		sh->tokens[x].d_quote = false;
		sh->tokens[x].f_quote = false;
		sh->tokens[x].file = false;
		x++;
	}
	// fazer aqui funcao de capturar os tokens e filtrar por tipo.
}


void	init_error(t_sh *sh)
{
	sh->error.cmd_error = false;
	sh->error.token_error = false;
	sh->error.expand_error = false;
	sh->error.parse_error = false;
	sh->error.exec_error = false;
}

void	free_tokens(t_sh *sh)
{
	/*
	while(sh->vars.tk_num > 0)
	{
			free(&sh->tokens[sh->vars.tk_num].tokens);
			sh->vars.tk_num--;
	}*/
	free(sh->tokens);
}


int main(int ac, char **av, char **envp)
{
   	t_sh	sh;
	int x;

	memset(&sh, 0, sizeof(t_sh));
	x = 0;
	init_error(&sh);
	while(1)
	{
		sh.vars.tk_num = 0;

		if(sh.cmd_line)
			free(sh.cmd_line);


		
		sh.cmd_line = readline("Input -> ");
		//	printf("\n\nbefore =%s-fim-", sh.cmd_line);

		sh.cmd_line = prepare_line(sh.cmd_line);
		//printf("\n\nafte1111111111111111r line =%s/fim/", sh.cmd_line);

		sh.vars.tk_num = count_tokens(&sh);

		init_tokens(&sh);
		//tokens_2_matrix(sh);



		//get_tokens(&sh);

		printf("\n\n out of it\n\n tk_num = %d\n cmd_line = %s\n\n\n\n", sh.vars.tk_num, sh.cmd_line);


		free_tokens(&sh);


	}




}