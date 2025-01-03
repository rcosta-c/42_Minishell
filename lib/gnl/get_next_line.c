/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:58:31 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/03 08:25:01 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_finalstr(char *buffer)
{
	int		x;
	char	*finalstr;

	x = 0;
	if (!buffer[x])
		return (NULL);
	while (buffer[x] && buffer[x] != '\n')
		x++;
	finalstr = malloc(sizeof(char) * (x + 2));
	if (!finalstr)
		return (NULL);
	x = 0;
	while (buffer[x] && buffer[x] != '\n')
	{
		finalstr[x] = buffer[x];
		x++;
	}
	if (buffer[x] == '\n')
	{
		finalstr[x] = buffer[x];
		x++;
	}
	finalstr[x] = '\0';
	return (finalstr);
}

char	*ft_nextgnl(char *buffer)
{
	int		x;
	char	*nextstr;

	x = 0;
	while (buffer[x] && buffer[x] != '\n')
		x++;
	if (!buffer[x])
	{
		free(buffer);
		return (NULL);
	}
	x++;
	nextstr = ft_substr(buffer, x, ft_strlen(buffer) - x);
	free(buffer);
	return (nextstr);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*final_str;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	buffer = ft_chunckjoin(fd, buffer, temp);
	if (temp)
		free(temp);
	if (!buffer)
		return (NULL);
	final_str = ft_finalstr(buffer);
	buffer = ft_nextgnl(buffer);
	return (final_str);
}
