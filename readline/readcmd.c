#include "../includes/minishell.h"

static	void init_sh(t_shvars *x)
{
	x->pipe = false;
	x->redirect = false;
	x->cmd_error = false;
	x->n_cmds = 0;
	x->cmd_len = 0;
	x->n_pipes = 0;
	x->n_redirect = 0;
}

static	bool count_cmds(char *str, t_shvars *x)
{
	int	c;

	init_sh(x);
	c = 0;
	if(str == NULL)
	{
		return(true);
	}
	x->cmd_len = ft_strlen(str); 
	while(str[c])
	{
		if(str[c] == '|' || str[c] == ';')
		{	if(str[c] == '|')
				x->n_pipes++;
			x->n_cmds++;
		}
		if(str[c] == '>' || str[c] == '<')
			x->n_pipes++;
		c++;
	}
	x->n_cmds++;
	c = 0;


	return(false);
}

static void	print_teste(char *str, t_shvars sh)
{
	printf("\n\n %s \n\n", str);
		printf("\n\n cmd_len = %d \n\n n_pipes=%d\n n_redirects=%d\n n_cmds=%d\n\n", \
			sh.cmd_len, sh.n_pipes, sh.n_redirect, sh.n_cmds);
}

static int check_exit(char *str)
{
	if(str[0] == 'e' && str[1] == 'x' && str[2] == 'i' && str[3] == 't') //verificacao para sair, a alterar
			return(1);
	else
			return(0);
}
int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_shvars	sh;

	
	
	/*
	
	VERIFICACAO DE MEMORIA, SE INVALIDA OU INSUF PARA INCIALIZAR MINISHELL

	
	
	*/



	while(1)
	{
		str = readline(get_prompt());
		if (check_exit(str))
			break;
		sh.cmd_error = count_cmds(str, &sh);
		if(sh.cmd_error == true)
			break;
		get_tokens(str, sh);
		
		
		print_teste(str, sh); //apagar depois.


		

		//add_history(str);
		free(str);
	
	
	}
		free(str);


	return(0);


}