/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:32:39 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/20 16:52:03 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	verify_the_verifier(char *temp, int x)
{
	while(temp[x])
	{
		if (temp[x] == '/')
			return (x);
		x++;
	}
	if (temp[x] == '\0')
	{
		free(temp);
		return (x);
	}
	else
		return (x);
}

static char	*verify_parse_redir_helper(char *temp)
{
	int		x;
	int		z;
	char	*new_temp;

	x = 0;
	z = ft_strlen(temp);
	x = verify_the_verifier(temp, x);
	if (x == z)
		return(NULL);
	new_temp = malloc(sizeof(char *) * (x + 1));
	x = 0;
	while(temp[x])
	{
		if (temp[x] == '/')
			break;
		new_temp[x] = temp[x];
		x++;
	}
	new_temp[x] = '\0';
	free(temp);
	return(new_temp);
}

bool	ft_parse_redirs_out_access(t_sh *sh, int n_cmd, int x)
{
	char	*temp = NULL;
	char	*ttemp = NULL;
	int		xx;

	xx = 0;
	ttemp = ft_strdup(sh->tokens[x].tokens);
	temp = verify_parse_redir_helper(ttemp);
	if (temp)
	{
		if (access(temp, F_OK) == -1)
		{
			free(temp);
			sh->comands[n_cmd].errors.outfile_noaccess = true;
			return (true);
		}
	}
	free(temp);
	return (false);
}
