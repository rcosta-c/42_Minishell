#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av, char **envp)
{
    char    **teste;
    int     x;

    x = 0;
    teste =envp;
    while(teste[x])
    {
        printf("%s\n", teste[x]);
        x++;
    }
    return(0);

}