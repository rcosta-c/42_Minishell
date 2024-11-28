#include "../includes/minishell.h"

// Retorna a posicao de uma variavel no envp ou -1 se nao encontrada
static int	get_var_pos(t_sh *sh, char *var)
{
	int	i;
	int	len;

	len = ft_strchr(var, '=') - var;
	if (len <= 0)
		return (-1);
	i = 0;
	while (i < sh->vars.envp_total)
	{
		if (!ft_strncmp(sh->envp[i], var, len) && sh->envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

// Adiciona ou atualiza uma variavel de ambiente
static void	update_var(t_sh *sh, char *var)
{
	int		var_pos;
	int		i;
	int		new_size;
	char	**envp_temp;

	var_pos = get_var_pos(sh, var);
	if (var_pos >= 0)
	{
		free(sh->envp[var_pos]);
		sh->envp[var_pos] = ft_strdup(var);
		return ;
	}
	new_size = sh->vars.envp_total + 2;
	envp_temp = ft_calloc(new_size, sizeof(char *));
	if (!envp_temp)
	{
		free(envp_temp);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < sh->vars.envp_total)
	{
		envp_temp[i] = ft_strdup(sh->envp[i]);
		if (!envp_temp[i])
		{
			free(envp_temp);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	envp_temp[i] = ft_strdup(var);
	if (!envp_temp[i])
	{
		free(envp_temp);
		exit(EXIT_FAILURE);
	}
	sh->vars.envp_total++;
	free(sh->envp);
	sh->envp = envp_temp;
}

// valida se uma string é um identificador de variavel apropriado.
static int	valid_var(char *var)
{
	int	i;

	if (!var || var[0] == '=' || ft_isdigit(var[0]))
		return (0);

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}

// executa a logica principal do comando export,
// permitindo que usuários adicionem ou modifiquem variaveis de ambiente.
void	ft_export(t_sh *sh, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (valid_var(args[i]))
		{
			if (ft_strchr(args[i], '='))
			{
				update_var(sh, args[i]);
				sh->error.exit_error = false;
			}
		}
		else
		{
			ft_putstr_fd(": export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			sh->error.exit_error = true;
		}
		i++;
	}
	if (!args[1])
		ft_env(sh, args);
}
