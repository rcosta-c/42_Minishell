#include <stdio.h>
#include <string.h>

int main(int ac, char **av, char **envp)
{
    int x;
    char *a="USER";

    x =0;
    while(envp[x])
    {
        if(envp[x][0] == 'U' && envp[x][1] == 'S' && envp[x][2] == 'E' && envp[x][3] == 'R')
            printf("\n%s", envp[x++]);
        else
            x++;
    }
    return(0);
}




static char	*ft_strjoin(char *s1, char *s2)
