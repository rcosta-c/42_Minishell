#include "../includes/minishell.h"

static char	*verify_home(t_sh *sh, char *prompt)
{
	char	*home;
	int		x;
	int		n_pr;
	int		n_total;
	char	*final_prompt;

	x = 0;
	home = search_envp(sh, "HOME");
	while(prompt[x])
	{
		if(x == 0 && prompt[x] != home[x])
			return(prompt);
		else if(prompt[x] == home[x])
		{
			x++;
		}
		else if(prompt[x] != home[x])
			break;
	}
	n_pr = ft_strlen(prompt);
	n_total = n_pr - x;
	final_prompt = malloc(sizeof(char) * n_total + 2);
	n_total = 1;
	if(x == 1)
		final_prompt[0] = '/';
	else
		final_prompt[0] = '~';
	while(prompt[x])
	{
		final_prompt[n_total] = prompt[x];
		n_total++;
		x++;
	}
	final_prompt[n_total] = '\0';
	return(final_prompt);
}

char	*join_2_str(char *a, char *b, char *z, int option)
{
	char	*res;
	char 	*temp;

	if (z)
	{
		temp = ft_strjoin(a, z);
		res = ft_strjoin(temp, b);
		free(temp);
	}
	else
		res = ft_strjoin(a, b);
	if(option == 1)
	{
		free(b);
		free(a);
	}
	if(option == 2)
		free(a);
	return(res);
}


char	*get_prompt(t_sh *sh)
{
	char	*user;
	char	*host;
	char	*dir;
	char	*prompt;
	char	*temp;

//printf("entrou no getrpompt\n");
	user = search_envp(sh, "USER");
	host = find_my_host(sh);
	//printf("%s\n", host);
	//host = NULL;
	prompt = join_2_str(user, host , "@", 0);
	
	dir = search_envp(sh, "PWD");
	dir = verify_home(sh, dir);
	temp = join_2_str(prompt, dir, ":", 0);
	free(prompt);
	prompt = join_2_str(temp, " ", "$", 0);
	free(temp);
	free(host);
	free(dir);
	return(prompt);  
}
