/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:27:36 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/19 10:33:23 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	x;
	unsigned int	len;

	if (size == 0)
		return (ft_strlen(src));
	len = 0;
	while (src[len])
		len++;
	x = 0;
	while (src[x] != '\0' && x < (size - 1))
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = '\0';
	return (len);
}
/*
int     main()
{
        char		x[] = "12345";
	char		d[] = "";
	size_t		r = ft_strlcpy(d, x, 5);

        printf("src: %zu, dest: %s \n", r, d);
} */
