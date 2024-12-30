/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:08:36 by cde-paiv          #+#    #+#             */
/*   Updated: 2024/12/30 09:21:02 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	compare_strings(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] < str2[i])
			return (-1);
		if (str1[i] > str2[i])
			return (1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	if (str1[i] == '\0')
		return (-1);
	return (1);
}

static void	sort(char **array, int n)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < n -1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (compare_strings(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array [j + 1];
				array[j + 1] = temp;
				i = 0;
				j = 0;
			}
			j++;
		}
		i++;
	}
}

void	free_temp_env(char **temp)
{
	int	x;

	x = 0;
	while (temp[x])
	{
		free(temp[x]);
		x++;
	}
	free(temp);
}

char	**handle_array(t_sh *sh)
{
	char	**temp_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (sh->envp[i])
		i++;
	temp_env = malloc((sh->vars.envp_total + 1) * sizeof(char **));
	if (!temp_env)
		return (NULL);
	while (j < sh->vars.envp_total)
	{
		temp_env[j] = ft_strdup(sh->envp[j]);
		j++;
	}
	temp_env[j] = NULL;
	sort(temp_env, j);
	return (temp_env);
}
