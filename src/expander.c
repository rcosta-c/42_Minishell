#include "../includes/minishell.h"

/* s1 = token part and s2 = envp part */
static int	ft_envp_n_cmp(const char *s1, const char *s2)
{
	size_t	counter;
	size_t n;

	n = ft_strlen(s1);
	counter = 0;
	if (n == 0)
		return (0);
	while (s1[counter] == s2[counter] && s1[counter] != '\0')
	{
		if (counter < (n - 1))
			counter++;
		else
			return (0);
	}
	if(s2[counter] == '=')
		return ((unsigned char)(s1[counter]) - (unsigned char)(s2[counter]));
	else
		return ((unsigned char)(s2[counter]));
}

static char	*search_envp(t_sh *sh, char *z)
{
	int 	x;
	int		xx;
	int		xt;
	char	temp[100];

	xx = 0;	
	x = 0;
	xt = 0;
	printf("\n\n expand parte procura por expands\n\n");
	while(sh->envp[x])
	{
		if(ft_envp_n_cmp(z, sh->envp[x]) == 0)
		{
			while(sh->envp[x][xx] != '=')
				xx++;
			xx++;
			while(sh->envp[x][xx])
				temp[xt++] = sh->envp[x][xx++];
			temp[xt] = '\0';
			return(ft_strdup(temp));
		}
		else
			x++;	
	}
	return(NULL);
}

void	expand_token(t_sh *sh, char *token, int n)
{
	char	a[100];
	char	b[100];
	char	c[100];
	char	*z;
	int		xa;
	int		xb;

	xa = 0;
	xb = 0;
	printf("\n\n entrou em expand token  1111 \n\n token=%s", token);
	while(sh->tokens[n].tokens[xa])// && (sh->tokens[n].tokens[xa] != 126 || sh->tokens[n].tokens[xa] != 36))
	{
				printf("\n\n caralhooo \n%d\n  parte 22222\n\n", token[xa]);

		if(token[xa] == 126 || token[xa] == 36)
			break;
		a[xa] = token[xa];
		xa++;
	}
	a[xa] = '\0';
	printf("\na = %s\n", a);

	printf("\n\n expand parte 2222 e nao sei mais \n\n");

	if(token[xa] == '~')
	{
		printf("\ncarlho tilde\n");
		z = search_envp(sh, "HOME");
		xa++;
	}
	else if(token[xa] == '$')
	{
			printf("\n\n expand parte 22222 e  2222222 \n%d\n\n", token[xa]);
		xa++;
		while(token[xa] >= 'A' && token[xa] <= 'Z')
			c[xb++] = token[xa++];
		c[xb] = '\0';
		z = search_envp(sh, c);
	}
	c[xb] = '\0';
	printf("\n\n expand parte 33333\n\n");
	xb = 0;
	if(token[xa])
	{ 	printf("\n\n expand parte 33333\n\n");

	while(token[xa])
		b[xb++] = token[xa++];
	}
		printf("\n\n expand parte 33333\n\n");

		printf("\n\n expand parte 33333\n\n");

	b[xb] = '\0';
		printf("\n\n\n a=%s , b=%s ,c=%s", a, b, z);

	printf("\n\n expand parte 4444\n\n");
	free(sh->tokens[n].tokens);
	sh->tokens[n].tokens = join_2_str(a, b, z);
	free(z);
}

void	search_expand(t_sh *sh)
{
	int	x;
	int n;

	n = 0;
	x = 0;
			printf("\n\n exapnd parte 0\n\n");

	while(n < sh->vars.tk_num)
	{
		if(sh->tokens[n].exp_e || sh->tokens[n].exp_t )
			expand_token(sh, sh->tokens[n].tokens, n);
		else if(sh->tokens[n].d_quote)// || sh->tokens[n].file))
		{
			while(sh->tokens[n].tokens[x])
			{
				if(sh->tokens[n].tokens[x] == '$')
					expand_token(sh, sh->tokens[n].tokens, n);
				
				x++;
			}
		}
		n++;
	}
}

/*
void	search_expand(t_sh *sh)
{
	int	x;
	int n;

	n = 0;
	x = 0;
	while(n < sh->vars.tk_num)
	{
		x = 0;
		printf("\n\n exapnd parte 0\n\n");
		if(sh->tokens[n].file || sh->tokens[n].d_quote || sh->tokens[n].exp_e || sh->tokens[n].exp_t)// || sh->tokens[n].arg)
		{
			while(sh->tokens[n].tokens[x])
			{
				printf("\n\n   expand parte 1\n\n");
				if(sh->tokens[n].tokens[x] == '~' && (sh->tokens[n].tokens[x + 1] == '/' || !sh->tokens[n].tokens[x + 1]) && sh->tokens[n].arg)
					expand_token(sh, sh->tokens[n].tokens, n);
			else if(sh->tokens[n].tokens[x] == '$' && sh->tokens[n].tokens[x + 1] >= 'A' && sh->tokens[n].tokens[x + 1] <= 'Z')// || (sh->tokens[n].tokens[x + 1] >= '0' && sh->tokens[n].tokens[x + 1] <= '9')))
					expand_token(sh, sh->tokens[n].tokens, n);
				x++;
			}
		}
		n++;
	}
}
*/

/*
int main()
{
	search_expand(sh);

}*/