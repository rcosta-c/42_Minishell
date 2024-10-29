#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool    compare_env(char *env, char *value)
{
    int xx;
    int x;

    x = 0;
    xx = 0;
    while(value[xx])
    {
        if(env[x] == value[xx])
        {
			x++;
			xx++;
		}
        else
            return(false);
    }
    return(false);
}

int main(int ac, char **av, char **envp)
{
    int x;
    char h[4] = "HOME";

    //*h = "HOME";
    x = 0;
    while(envp[x])
	{
        if(compare_env(envp[x], h))
            printf("\n\n%s\n\n", envp[x]);

//        if(strcmp(envp[x], h) == 0)
  //          printf("\n\n%s\n\n", envp[x]);
        else
            x++;
	}







}