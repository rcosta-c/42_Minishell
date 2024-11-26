/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:43:36 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/10/28 09:33:53 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	counter;
	char	*n_str;
	size_t	max_len;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	n_str = (char *)malloc(len + 1);
	if (!n_str)
		return (NULL);
	counter = start;
	max_len = 0;
	while (counter < ft_strlen(s) && max_len < len)
	{
		n_str[max_len] = s[counter];
		max_len++;
		counter++;
	}
	n_str[max_len] = '\0';
	return (n_str);
}
/*
#include <stdio.h>

int     main()
{
        char            *x = "USER=rcosta";
	 	char 	n = '=';
	size_t		len = 11;
        char            *d;

        d = ft_substr(x, 4, len);
	printf("%s \n", d);
}
*/