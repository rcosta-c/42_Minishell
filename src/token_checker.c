#include "../includes/minishell.h"

bool token_is_valid(char *src)
{
	if(*src == 33 || (*src >= 35 && *src <= 126))
		return(true);
	else if(*src == 9)
		return(true);
	else
		return(false);
}

int	check_dquote(char *str, int counter)
{
	int 	temp;

	temp = counter;
	if(str[temp] == 34)
	{
		temp++;
		while(str[temp] && str[temp] != 34)
			temp++;
		if(str[temp] == '\0')
			return(counter);
		else
		{
			temp++;
			return(temp);
		}
	}
	return(counter);
}

int	check_squote(char *str, int counter)
{
	int 	temp;

	temp = counter;
	if(str[temp] == 39)
	{
		temp++;
		while(str[temp] && str[temp] != 39)
			temp++;
		if(str[temp] == '\0')
			return(counter);
		else
		{
			temp++;
			return(temp);
		}
	}
	return(counter);
	
}

int check_type_quote(char *cmd_line, int x)
{
	if(cmd_line[x] == 34)
	{
		return(check_dquote(cmd_line, x));
	}
	else if(cmd_line[x] == 39)
	{
		return(check_squote(cmd_line, x));
	}
	else
		return(x);
}
