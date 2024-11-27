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

char	*search_envp(t_sh *sh, char *z)
{
	int 	x;
	int		xx;
	int		xt;
	char	temp[500];

	xx = 0;	
	x = 0;
	xt = 0;
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


void    expand_token(t_sh *sh, char *token, int n)
{
    char    a[500];
    char    b[500];
    char    *c;
    char    *z;
    int     xa;
    int     xb;
    int     x;
    int     exp_counter;
	pid_t	pid;

	(void)token;
    exp_counter = 0;
	x = 0;
	z = NULL;
//	printf("\n\n -> %d -> %s", n, token);
    while(sh->tokens[n].tokens[x])
    {
        if(sh->tokens[n].tokens[x] == '$' && sh->tokens[n].tokens[x + 1] >= 'A' && sh->tokens[n].tokens[x + 1] <= 'Z' && sh->tokens[n].s_quote == false)
            exp_counter++;
		else if(sh->tokens[n].tokens[x] == '~' && sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false)
			exp_counter++;
		else if(sh->tokens[n].tokens[x] == '$' && (sh->tokens[n].tokens[x + 1] == '$' || sh->tokens[n].tokens[x + 1] == '?'))
			exp_counter++;
        x++;
    }
//	printf("\n\n 1 exp_counter = %d\n\n", exp_counter);
	x = 0;
	while(sh->tokens[n].tokens[x])
	{
		xa = 0;	
		xb = 0;
		while(sh->tokens[n].tokens[x])
		{
			if (sh->tokens[n].tokens[x] == '$' || sh->tokens[n].tokens[x] == '~')
				break;
			a[xa++] = sh->tokens[n].tokens[x++];
		}
//		printf("valor de x -> %d", x);
		a[xa] = '\0';
		z = join_2_str(z, a, NULL);
		if(sh->tokens[n].tokens[x] == '~' && sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false)
		{
			c = search_envp(sh, "HOME");
			x++;
		}
		else if(sh->tokens[n].tokens[x] ==  '$' && sh->tokens[n].tokens[x + 1] == '$')
		{
			x++;
//			printf("acabar de definir esta passo\n");
			pid = getpid();
			c = ft_itoa(pid);
			x++;
		}
		else if(sh->tokens[n].tokens[x + 1] ==  '?' && sh->tokens[n].tokens[x] == '$')
		{
			x++;
			c = "99";
			x++;
		}
		else if(sh->tokens[n].tokens[x] == '$')
		{
			x++;
			while((sh->tokens[n].tokens[x] >= 'A' && sh->tokens[n].tokens[x] <= 'Z') || sh->tokens[n].tokens[x] == '$' || sh->tokens[n].tokens[x] == '?')
				b[xb++] = sh->tokens[n].tokens[x++];
			b[xb] = '\0';
//			printf("\n e aquinao??? \nHEYHEY HEY\n%s\n", b);
			c = search_envp(sh, b);
		}
//		printf("\n\n aqui = %s\n exp_counter = %d\n", c, exp_counter);
		z = join_2_str(z, c, NULL);
		exp_counter--;
		if (exp_counter == 0)
		{
			xa = 0;
			while(sh->tokens[n].tokens[x])
				a[xa++] = sh->tokens[n].tokens[x++];
			a[xa] = '\0';
			z = join_2_str(z, a, NULL);
			break;
		}
	}
//	printf("FINAL EXPAND = %s", z);

	//free(sh->tokens[n].tokens);
	sh->tokens[n].tokens = z;
//	printf("FINAL EXPAND = %s", sh->tokens[n].tokens);

	//free(z);

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
//		printf("fim de expand\n\n");
		n++;
	}
}
