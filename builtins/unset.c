#include "../includes/minishell.h"

//remove uma variavel de ambiente do array envp
void	ft_unset(t_sh *sh, char **args)
{
	int		i;
	int		j;
	char	**envx;

	if (!args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return ;
	}
	i = 0;
	while (sh->envp[i])
		i++;
	envx = malloc(sizeof(char *) * i);
	if (!envx)
		return ;
	i = 0;
	j = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], args[1], ft_strlen(args[1])) != 0
			|| sh->envp[i][ft_strlen(args[1])] != '=')
		{
			envx[j] = ft_strdup(sh->envp[i]);
			j++;
		}
		free(sh->envp[i]);
		i++;
	}
	envx[j] = NULL;
	free(sh->envp);
	sh->envp = envx;
}
