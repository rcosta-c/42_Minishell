#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char    *replace_env(char *env)
{
    int x;
    char    *new;

    x = 0;
    while(env[x] && env[x] != '=')
        x++;
    new = strdup(&env[++x]);
    return(new);
}

bool    compare_env(char *env, char *value)
{
    int len;
    int x;

    x = 0;
    len = strlen(value);
    while(x < len && value[x])
    {
        if(env[x] == value[x])
            x++;
        else
            return(false);
    }
    if(x == len)
        return(true);
    return(false);

}

int main(int ac, char **av, char **envp)
{
    int x;
    int len;
    char *dest;

    x =0;
    len = 0;
    while(envp[x])
    {
        len = strlen(av[1]);
        if(compare_env(envp[x], av[1]))
        {
            dest = replace_env(envp[x]);
            printf("\n\n%s\n\n", dest);
            printf("\n\naqui esta: %s=%s\n\n,", av[1], envp[x++]);
            x++;
            free(dest);
        }
        else
            x++;
    }
    return(0);
}




//static char	*ft_strjoin(char *s1, char *s2)
