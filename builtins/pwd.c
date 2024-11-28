#include "../includes/minishell.h"

//imprime o diretório de trabalho atual,
// ou exibe uma mensagem de erro caso não consiga acessá-lo
void	ft_pwd(t_sh *sh, char **args)
{
	size_t	i;
	char	*temp;

	if (!args[1])
	{
		i = 0;
		while (sh->envp && ft_strncmp(sh->envp[i], "PWD=", 4))
			i++;
		if (sh->envp && sh->envp[i])
		{
			temp = ft_substr(sh->envp[i], 4, ft_strlen(sh->envp[i]));
			ft_putstr_fd(temp, 1);
			ft_putstr_fd("\n", 1);
			free(temp);
		}
		else
		{
			ft_putstr_fd("pwd: error retrieving current directory:\n", 2);
			ft_putstr_fd("getcwd: cannot access parent directories:\n", 2);
			ft_putstr_fd("No such file or directory\n", 2);
			sh->error.exit_error = true;
		}
	}
}
