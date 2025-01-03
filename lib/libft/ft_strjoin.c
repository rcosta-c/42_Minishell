/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:50:54 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/03 08:20:45 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	counter;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!newstr)
		return (NULL);
	counter = 0;
	while (*s1)
	{
		newstr[counter++] = *s1++;
	}
	while (*s2)
	{
		newstr[counter++] = *s2++;
	}
	newstr[counter] = '\0';
	return (newstr);
}
/*
int     main()
{
        const char    s[] = "mento";
        const char    d[] = "casa";
	char		*resultado; 

	resultado = ft_strjoin(d,s);
        printf(" resuldo ft_strjoin:%s\n", ft_strjoin(d, s));
}*/
