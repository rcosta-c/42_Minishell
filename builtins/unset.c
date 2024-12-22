/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:16:01 by mota              #+#    #+#             */
/*   Updated: 2024/12/22 08:28:45 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	check_wrong_args(char **args)
{
	int	x;
	int	xx;

	xx = 0;
	if(!args[1])
	{
		g_status = 0;
		return (true);
	}

	while (args[xx])
	{
		x = 0;
		while (args[xx][x])
		{
			if (args[xx][x] == '=')
			{
				printf("unset: %s: invalid parameter name\n", args[xx]);
				return (true);
			}
			x++;
		}
		xx++;
	}
	return (false);
}

void	ft_unset(t_sh *sh, char **args)
{
	int		i;
	int		j;
	char	**envx;

	i = 0;
	j = 0;
	if (check_wrong_args(args) == true)
		return ;
	envx = malloc(sizeof(char *) * (sh->vars.envp_total ));
	if (!envx)
		return ;
	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], args[1], ft_strlen(args[1])) != 0 || sh->envp[i][ft_strlen(args[1])] != '=')
		{
			envx[j] = ft_strdup(sh->envp[i]);
			j++;
		}
		i++;
	}
	envx[j] = NULL;
	free_env(sh);
	sh->envp = envx;
	sh->vars.envp_total--;
}
