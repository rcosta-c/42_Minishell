#include "../includes/minishell.h"

void	ft_getenv(t_sh *sh, char **envp)
{
	int	x;

	x = 0;
	while (envp[x] && envp)
	{
		x++;
	}
	sh->vars.envp_total = x;
	sh->envp = malloc(sizeof(char *) * (x + 1));
	if (!sh->envp)
		return ;
	x = 0;
	while (envp[x] && x < sh->vars.envp_total)
	{
		sh->envp[x] = envp[x];
		x++;
	}
	sh->envp[x] = NULL;
}

char	*find_my_host(t_sh *sh)
{
	int		x;
	int		xx;
	char	*temp;
	char	temp2[20];

	x = 0;
	xx = 0;
	temp = search_envp(sh, "SESSION_MANAGER");
	while (temp[x] != '/')
		x++;
	x++;
	while (temp[x] != '.')
	{
		temp2[xx++] = temp[x++];
	}
	temp2[xx] = '\0';
	return (ft_strdup(temp2));
}

/*
char *find_my_host(t_sh *sh, char *str)
{
	int x;

	x = 0;
	//printf("\n entrou no find my env\n");
	while(sh->envp[x])
	{
		//printf("%s\n", sh->envp[x]);
		if(ft_strncmp(sh->envp[x], str, ft_strlen(str)) == 0)
		{
			return(ft_substr(sh->envp[x], ft_strlen(str), ft_strlen(sh->envp[x])));
		}
		x++;
	}
	return(NULL);
}*/

/*
char    **ft_getenv(t_sh *sh, char **envp, char **merda)
{
	int x;
	
	x = 0;
	while(envp[x] && envp)
	{
		x++;
	}
	sh->vars.envp_total = x;
	merda = malloc(sizeof(char *) * (x + 1));
	if(!sh->envp)
		return(NULL);
	x = 0;
	while(envp[x] && x < sh->vars.envp_total)
	{
		merda[x] = envp[x];
		x++;
	}
	merda[x] = NULL; 
	return(merda); 

}


int main(int ac, char **av, char **envp)
{
	t_sh    *sh;
	int x = 0;
	char **merda;
	int     total;

	//merda = ft_getenv(sh, envp, merda);

	while(envp[x] && envp)
	{
		x++;
	}
	total = x;
	merda = malloc(sizeof(char *) * (x + 1));
//    if(!sh->envp)
  //      return(0);
	x = 0;
	while(envp[x] && x < total)
	{
		merda[x] = envp[x];
		x++;
	}
	merda[x] = NULL; 
	x = 0;
	while(merda[x])
	{
		printf("%s\n", merda[x]);
		x++;
	}
	printf("%d\n", total);
	free(merda);
	return(0);

}*/
