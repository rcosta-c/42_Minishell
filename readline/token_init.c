#include "./includes/minishell.h"

static int	check_quote(char *str, int counter)
{
	int 	temp;

	temp = counter;
	if(str[temp] == 34)
	{
		temp++;
		while(str[temp] && str[temp] != 34)
			temp++;
		//if(str[temp] == '\0')
		//	return(counter);
		if(str[temp] == 34)
		{
			temp++;
			return(temp);
		}
	}
	return(counter);
}

static int count_tokens(char *str, t_tokens tokens)
{
	int x;
	int tk_n;

	x = 0;
	tokens.tk_num = 0;
	while(str[x])
	{
		x = check_quote(str, x);
		if(str[x] == 32 || str[x] == 9)
		{
			while(str[x + 1] == 32 || str[x + 1] == 9)
				x++;
			x++;
			tokens.tk_num++;
		}
		/*if(str[x] == '|' || str[x] == '>' || str[x] == '<' || str[x] == ;)
		{
			tk_n;
			x++;
		}*/
		
	if(str[x + 1] == '\0')
		tokens.tk_num++;

		x++;





	}

	printf("\n\n\n string: %s\n number of tokens: %d", str, tokens.tk_num);

	return(tk_n);




}
/*
static char analise_prepare_token(char *str)
{


}
*/




void    get_tokens(char *str, t_shvars sh)
{
//	char    **tokens;
	t_tokens	tokens;
	
	memset(&tokens, 0, sizeof(t_tokens));
	count_tokens(str, tokens);
	//token = analise_prepare_token(str, count_tokens(str));







}