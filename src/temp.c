#include "../includes/minishell.h"

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
static char	*verify_home(t_sh *sh, char *prompt)
{
	char	*home;
	int		x;
	int		n_pr;
	int		n_total;
	char	*final_prompt;

	x = 0;
	home = search_envp(sh, "HOME");
	while(prompt[x])
	{
		if(x == 0 && prompt[x] != home[x])
			return(prompt);
		else if(prompt[x] == home[x])
		{
			x++;
		}
		else if(prompt[x] != home[x])
			break;
	}
	n_pr = ft_strlen(prompt);
	n_total = n_pr - x;
	final_prompt = malloc(sizeof(char) * n_total + 2);
	n_total = 1;
	if(x == 1)
		final_prompt[0] = '/';
	else
		final_prompt[0] = '~';
	while(prompt[x])
	{
		final_prompt[n_total] = prompt[x];
		n_total++;
		x++;
	}
	final_prompt[n_total] = '\0';
	return(final_prompt);
}

char *find_my_host(t_sh *sh)
{
	int x;
	int	xx;
	char *temp;
	char *temp2;

	x = 0;
	xx = 0;
	temp = search_envp(sh, "SESSION_MANAGER");
	temp2 = malloc(sizeof(char *) * 20);
	while(temp[x] != '/' && temp[x])
		x++;
	x++;	
	while(temp[x] != ':' && temp[x])
	{
		temp2[xx++] = temp[x++];
	}
	temp2[xx] = '\0';
	free(temp);
	return(ft_strdup(temp2));
}

char	*join_2_str(char *a, char *b, char *z)
{
	char	*res;
	char 	*temp;

	if (z)
	{
		temp = ft_strjoin(a, z);
		res = ft_strjoin(temp, b);
		free(temp);
	}
	else
		res = ft_strjoin(a, b);
	return(res);
}


char	*get_prompt(t_sh *sh)
{
	char	*user;
	char	*host;
	char	*dir;
	char	*prompt;
	char	*temp;

//printf("entrou no getrpompt\n");
	user = search_envp(sh, "USER");
	host = find_my_host(sh);
	//printf("%s\n", host);
	prompt = join_2_str(user, host , "@");
	dir = search_envp(sh, "PWD");
	dir = verify_home(sh, dir);
	temp = join_2_str(prompt, dir, ":");
	free(prompt);
	prompt = join_2_str(temp, " ", "$");
	free(temp);
	free(host);
	free(dir);
	return(prompt);  
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter < n)
	{
		((unsigned char *)s)[counter] = c;
		counter++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (nmemb && size && nmemb > (UINT_MAX / size))
		return (NULL);
	dest = (void *)malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}

int main(int ac, char **av, char **envp)
{
    char    *prompt;
  	t_sh	*sh;

    	sh = ft_calloc(1, sizeof(t_sh));



	prompt = get_prompt(sh); //----------VERIFICAR LEAKS AQUI!!!!




}