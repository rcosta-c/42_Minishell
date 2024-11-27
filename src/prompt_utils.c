#include "../includes/minishell.h"

void    ft_getenv(t_sh *sh, char **envp)
{
    int x;
    char **temp;

    x = 0;
    while(envp[x] && envp)
    {
        x++;
    }
    sh->vars.envp_total = x;
    temp = malloc(sizeof(char *) * (x + 1));
    if(!temp)
        return;
    x = 0;
    while(envp[x] && x < sh->vars.envp_total)
    {
        temp[x] = envp[x];
        x++;
    }
    temp[x] = NULL; 
    sh->envp = temp;
    free(temp);
}

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