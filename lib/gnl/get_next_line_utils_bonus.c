/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:36:20 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/05/24 09:08:42 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	ft_bufferlen(char *x)
{
	int	len;

	len = 0;
	if (x)
		while (x[len])
			len++;
	return (len);
}

char	*ft_strchunckjoin(char *buffer, char *chunck)
{
	int		counter;
	int		total_len;
	char	*temp;
	char	*ptr_buffer;

	if (!buffer || !chunck)
		return (NULL);
	ptr_buffer = buffer;
	total_len = ft_bufferlen(buffer) + ft_bufferlen(chunck);
	temp = malloc(sizeof(char) * total_len + 1);
	if (!temp)
		return (NULL);
	counter = 0;
	while (*buffer)
		temp[counter++] = *buffer++;
	while (*chunck)
		temp[counter++] = *chunck++;
	temp[counter] = '\0';
	if (ptr_buffer)
		free (ptr_buffer);
	return (temp);
}
