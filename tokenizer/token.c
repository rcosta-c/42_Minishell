#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../includes/minishell.h"

static int	check_quote(char *str, int *counter)
{
	int 	temp;

	temp = *counter;
    printf("\n\n%d\n\n\n", temp);
	if(str[temp] == 34)
	{
		temp++;
        printf("filatrar");
		while(str[temp] && str[temp] != 34)
		{
            printf("e esta hein?\n\n");
            temp++;
        }	
		//if(str[temp] == '\0')
		//	return(counter);
		if(str[temp] == '\0')
            return(*counter);
        else
		{
            printf("\n\nesta a sair do filtro\n\n\n");
			temp++;
			return(temp);
		}
	}
    return(*counter);
	
}

static int count_tokens(char *str, t_tokens tokens)
{
	int x;
	int tk_n;

	x = 0;
	tokens.tk_num = 0;
	while(str[x])
	{
        if(x == 0 && isalpha(str[x]) && str[x] != 32)
            tokens.tk_num++;
		x = check_quote(str, &x);
		if(str[x] == 32 || str[x] == 9)
		{
			while(str[x + 1] == 32 || str[x + 1] == 9)
				x++;
			tokens.tk_num++;
		}
		/*if(str[x] == '|' || str[x] == '>' || str[x] == '<' || str[x] == ;)
		{
			tk_n;
			x++;
		}*/
		
	/*if(str[x + 1] == '\0')
		tokens.tk_num++;
    */
		x++;





	}

	printf("\n\n\n string: %s\n number of tokens: %d\n\n\n", str, tokens.tk_num);

	return(tk_n);




}
/*
static char analise_prepare_token(char *str)
{


}
*/

static char    *clean_line(char *str)
{
    int     x;
    int     xx;
    char    *newline;
    x = 0;
    xx = 0;
    newline = malloc(sizeof(char *) * (strlen(str) * 2));
    if(str[x] == 32)
    {
        while(str[x] == 32)
            x++;
    }
    while(str[x])
    {
        if(isalpha(str[x]))
        {
            newline[xx] = str[x];
            x++;
            xx++;
        }
        if(str[x] == ' ')
        {
            newline[xx] = ',';
            xx++;
            newline [xx] = ' ';
            xx++;
            x++;
            while(str[x] == 32)
                x++;
        }
    }
    newline[xx] = '\0';
    return(newline);

}


void    get_tokens(char *str, t_shvars sh)
{
//	char    **tokens;
	t_tokens	tokens;
	
	memset(&tokens, 0, sizeof(t_tokens));

	count_tokens(str, tokens);
	//token = analise_prepare_token(str, count_tokens(str));

    str = clean_line(str);
    printf("\n\n the string \n %s \n\n", str);







}


int main(void)
{
    char    *line;
   	t_shvars	sh;

    while(1)
    {
        line = readline("Input -> ");
        get_tokens(line, sh);





    }




}