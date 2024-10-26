#include "../includes/minishell.h"

bool	check_if_dquote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	while(str[x])
	{
		if(str[x] == 34)
			counter++;
		x++;
	}
	if(counter % 2 != 0)
		return(true);
	else
		return(false);
}

bool	check_if_squote(char *str, int x_o)
{
	int	x;
	int	counter;

	counter = 0;
	x = x_o + 1;
	while(str[x])
	{
		if(str[x] == 39)
			counter++;
		x++;
	}
	if(counter % 2 != 0)
		return(true);
	else
		return(false);
}

bool	search_ext(char *str)
{
	int	len;

	len = ft_strlen(str);
	while(len > 0)
	{
		if(str[len] == '.')
			return(true);
		len--;
	}
	return(false);
}
