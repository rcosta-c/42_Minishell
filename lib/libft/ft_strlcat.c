/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:04 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/29 08:44:03 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	s;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size == 0)
		return (src_len);
	if (size <= dst_len)
		return (src_len + size);
	s = 0;
	while (src[s] != '\0' && dst_len + 1 < size)
	{
		dst[dst_len] = src[s];
		dst_len++;
		s++;
	}
	dst[dst_len] = '\0';
	return (dst_len + ft_strlen(&src[s]));
}
/*
int     main()
{
        const char    s[] = "mento";
        char    d[] = "casa";
        size_t  r = ft_strlcat(d, s, 3);

        printf(" original: %s \n dest : %s \n r: %zu \n", s, d, r);

}*/
