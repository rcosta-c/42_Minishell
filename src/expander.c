#include "../includes/minishell.h"

/* s1 = token part && s2 = envp part */
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
	while(sh->tokens[n].tokens[xa])
	{
		if(token[xa] == 126 || token[xa] == 36)
			break;
		a[xa] = token[xa];
		xa++;
	}
	a[xa] = '\0';
	if(token[xa] == '~')
	{
		z = search_envp(sh, "HOME");
		xa++;
	}
	else if(token[xa] == '$')
	{
		xa++;
		while(token[xa] >= 'A' && token[xa] <= 'Z')
			c[xb++] = token[xa++];
		c[xb] = '\0';
		z = search_envp(sh, c);
	}
	c[xb] = '\0';
 		xb = 0;
	if(token[xa])
	{
		while(token[xa])
			b[xb++] = token[xa++];
	}
	b[xb] = '\0';
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
	while(n < sh->vars.tk_num)
	{
		if(sh->tokens[n].exp_e || sh->tokens[n].exp_t )
			expand_token(sh, sh->tokens[n].tokens, n);
		else if(sh->tokens[n].d_quote)
		{
			while(sh->tokens[n].tokens[x++])
			{
				if(sh->tokens[n].tokens[x] == '$')
					expand_token(sh, sh->tokens[n].tokens, n);
			}
		}
		else if(sh->tokens[n].file)
		{
			while(sh->tokens[n].tokens[x++])
			{
				if(sh->tokens[n].tokens[x] == '~')
					expand_token(sh, sh->tokens[n].tokens, n);
			}
		}
		n++;
	}
}
