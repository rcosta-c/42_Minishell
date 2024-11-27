#include "../includes/minishell.h"

void    ft_getenv(t_sh *sh, char **envp)
{
	int x;
	
	x = 0;
	while(envp[x] && envp)
	{
		x++;
	}
	sh->vars.envp_total = x;
	sh->envp = malloc(sizeof(char *) * (x + 1));
	if(!sh->envp)
		return;
	x = 0;
	while(envp[x] && x < sh->vars.envp_total)
	{
		//printf("%s\n",envp[x]);
		sh->envp[x] = envp[x];
		x++;
	}
	sh->envp[x] = NULL; 
}

char *find_my_host(t_sh *sh)
{
	int x;
	int	xx;
	char *temp;
	char temp2[20];

	x = 0;
	xx = 0;
	temp = search_envp(sh, "SESSION_MANAGER");
	while(temp[x] != '/')
		x++;
	x++;	
	while(temp[x] != '.')
	{
		temp2[xx++] = temp[x++];
	}
	temp2[xx] = '\0';
	return(ft_strdup(temp2));
}
