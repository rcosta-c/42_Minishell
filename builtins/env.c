#include "../includes/minishell.h"

// Exibe todas as variáveis de ambiente, 
//ou uma mensagem de erro caso haja argumentos adicionais
void	ft_env(t_sh *sh, char **args)
{
	size_t	i;

	if (args[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		sh->error.exit_error = true;
		return ;
	}
	else
	{
		i = 0;
		while (sh->envp[i])
		{
			ft_putstr_fd(sh->envp[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		sh->error.exit_error = false;
	}
}
