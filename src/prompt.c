#include "../includes/minishell.h"

static char	*verify_host(char *host)
{
	int		x;
	char	*res;

	x = 0;
	while(host[x])
	{
		if(host[x] == '.')
		{
			break;
		}
		x++;
	}
	res = malloc(sizeof(char) * (x + 1));
	x = 0;
	while(host[x] != '.' && host[x])
	{
		res[x] = host[x];
		x++;
	}
	res[x] = '\0';
	free(host);
	return(res);
}

static char	*verify_home(char *prompt)
{
	char	*home;
	int		x;
	int		n_pr;
	int		n_total;
	char	*final_prompt;

	x = 0;
	home = getenv("HOME");
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

char	*join_2_str(char *a, char *b, char *z)
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
	return(res);
}


char	*get_prompt()
{
	char	*user;
	char	*host;
	char	*dir;
	char	*prompt;
	char	*temp;

	user = getenv("USER");
	host = malloc(sizeof(char) * _SC_HOST_NAME_MAX + 1);
	gethostname(host, _SC_HOST_NAME_MAX + 1);
	host = verify_host(host);
	prompt = join_2_str(user, host , "@");
	dir = getenv("PWD");
	dir = verify_home(dir);
	temp = join_2_str(prompt, dir, ":");
	free(prompt);
	prompt = join_2_str(temp, " ", "$");
	free(temp);
	free(host);
	free(dir);
	return(prompt);  
}
/*
int	main(void)
{
	char *a;

	a = get_prompt();
	
	printf("\n%s\n", a);
	free(a);
	
}*/
