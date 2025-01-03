/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:36:20 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/03 08:24:52 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_search_nl(const char *x, int flag)
{
	if (x == NULL)
		return (NULL);
	while (*x)
	{
		if ((unsigned char)*x == (unsigned char)flag)
			return ((char *)x);
		x++;
	}
	if ((*x == '\0') && (flag == '\0'))
		return ((char *)x);
	return (NULL);
}

char	*ft_chunckjoin(int fd, char *buffer, char *temp)
{
	int		temp_len;
	char	*new_buffer;

	temp_len = 1;
	while (!ft_search_nl(buffer, '\n') && temp_len != 0)
	{
		temp_len = read(fd, temp, BUFFER_SIZE);
		if (temp_len == -1)
			return (NULL);
		temp[temp_len] = '\0';
		new_buffer = ft_strjoin(buffer, temp);
		if (!new_buffer)
		{
			free(buffer);
			return (NULL);
		}
		free(buffer);
		buffer = new_buffer;
	}
	return (buffer);
}
