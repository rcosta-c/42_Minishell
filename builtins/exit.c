#include "../includes/minishell.h"

// Verifica se a string e um numero valido
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Funcao para encerrar o shell validando argumentos e encerrando
void	ft_exit(t_sh *sh, char **args)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 2);
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		sh->error.exit_error = true;
		return ;
	}
	if (args[1] && !is_valid_number(args[1]))
	{
        free_exit(sh);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255); //Encerra com codigo de erro 255 para argumento invalido(nao sei se ode usar
	}
	if (args[1])
		exit_code = ft_atoi(args[1]);
	else
		exit_code = 0;
    free_exit(sh);
	exit(exit_code);
}