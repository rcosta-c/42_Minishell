#include "../includes/minishell.h"

char	*replace_tilde(char *env, char *tk)
{





}

char    *replace_env(char *env, char *tk)
{
    int x;
	int	xx;
	int	xxx;
	char	*n_env;
    char    new[200];

	xxx = 0;
	xx = 0;
    x = 0;
	while (tk[xx] != '$' && tk[xx])
		new[xx] = tk[xx++];
	xxx = xx;
	while(tk[xx] != ' ' && tk[xx])
		xx++;
    while(env[x] && env[x] != '=')
        x++;
	x++;
	while(env[x] && env[x] != ' ')
		new[xxx++] = env[x++];
	while(tk[xx])
		new[xxx++] = tk[xx++];
    n_env = strdup(new);
    return(new);
}

bool    compare_env(char *env, char *value)
{
    int len;
    int x;

    x = 0;
    len = strlen(value);
    while(x < len && *value)
    {
        if(env[x] == *value)
        {
			x++;
			*value++;
		}
        else
            return(false);
    }
    return(false);
}

static char replace_exp_e(t_sh *sh, char *tk, int x)
{
	int env_x;
    int len;
    char *dest;

	env_x = 0;
    len = 0;
    while(sh->envp[env_x])
    {
        len = ft_strlen(tk);
        if(compare_env(sh->envp[x], &tk[x]))
            dest = replace_env(sh->envp[x++], tk);
        else
            env_x++;
    }
	if(!sh->envp[x])
		return('\n');
	return(dest);
}


static char	get_env_home(t_sh *sh)
{
	int	x;

	x = 0;
	while(sh->envp[x])
	{





		
		x++;
	}





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
	home = get_env_home();
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