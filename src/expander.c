#include "../includes/minishell.h"

replace_expand(t_sh *sh, char *tk, int )
{



}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	size_t	counter;

	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!newstr)
		return (NULL);
	counter = 0;
	while (*s1)
	{
		newstr[counter++] = *s1++;
	}
	while (*s2)
	{
		newstr[counter++] = *s2++;
	}
	newstr[counter] = '\0';
	return (newstr);
}


static void	replace_exp_t(t_sh *sh, char *tk)
{
	char	*home;
	int		x1;
	int		x2;
	int		counter;

	x1 = 0;
	x2 = 0;
	counter = 0;
	home = getenv("HOME");
	while(tk[x1] != '~')
		x1++;
	if(!tk[x1 + 1])
	{
		tk = home;
		exit;
	}
	else
	{


	}





}


bool	search_expand(t_sh *sh, char *tk, int n)
{
	int	x;

	x = 0;
	if(sh->tokens[n].file || sh->tokens[n].d_quote || sh->tokens[n].envp || sh->tokens[n].arg)
	{
		while(tk[x])
		{
			if(tk[x] == '~' && (tk[x + 1] == '/' || !tk[x + 1]))
			{
				sh->tokens[n].exp_t = true;
				return(true);
				//tk = expand_home(tk);
			}
			else if(tk[x] == '$' && ((tk[x + 1] >= 'A' && tk[x + 1] <= 'Z') || (tk[x + 1] >= '0' && tk[x + 1] <= '9')))
			{
				sh->tokens[n].exp_e = true;
				return(true);
			}
			else if(tk[x] == '$' && !tk[x + 1])
			{
				printf("$\n");
				return(false);
			}
			x++;
		}
	}
}

void    expand_init(t_sh *sh)
{
	int x;
	while(x < sh->vars.tk_num)
	{
		if(search_expand(sh, sh->tokens[x].tokens, x))
		{
			if(sh->tokens[x].exp_e)
				replace_exp_e(sh, sh->tokens[x].tokens, x);
			else if(sh->tokens[x].exp_t)
				replace_exp_t(sh, sh->tokens[x].tokens)
			x++;
		}
		else
			x++;
	}
}


int main()
{

	expand_init(sh);





}