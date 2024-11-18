//#include "../includes/minishell.h"

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
    char    *expands[20];

    exp_counter = 0;
	x = 0;
	z = NULL;
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
	x = 0;
	while(sh->tokens[n].tokens[x] && exp_counter > 0)
	{
		xa = 0;
		xb = 0;
		while(sh->tokens[n].tokens[x] && (sh->tokens[n].tokens[x] != '~' || sh->tokens[n].tokens[x] != '$'))
			a[xa++] = sh->tokens[n].tokens[x++];
		a[xa] = '\0';
		z = join_2_str(z, a, NULL);
		if(sh->tokens[n].tokens[x] == '~' && sh->tokens[n].d_quote == false && sh->tokens[n].s_quote == false)
		{
			c = search_envp(sh, "HOME");
			x++;
		}
		else if(sh->tokens[n].tokens[x] == '$')
		{
			x++;
			while((sh->tokens[n].tokens[x] >= 'A' && sh->tokens[n].tokens[x] <= 'Z') || sh->tokens[n].tokens[x] == '$' || sh->tokens[n].tokens[x] == '?')
				b[xb++] = sh->tokens[n].tokens[x++];
			b[xb] = '\0';
			c = search_envp(sh, b);
		}
		z = join_2_str(z, c, NULL);
		exp_counter--;
		//x++;
	}
	sh->tokens[n].tokens = z;
	free(z);

}