/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:29:36 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/24 10:47:17 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	max_len;

	if (!s1 || !set)
		return (0);
	max_len = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	max_len = ft_strlen(s1);
	while (max_len && ft_strchr(set, s1[max_len]))
		max_len--;
	return (ft_substr(s1, 0, max_len + 1));
}
/*
int     main()
{
        char  	*string = "---umdolita---";
	char  	*x = "-";
        printf(" antes do resuldo de ft_strtrim:\n%s\n", string);
	printf(" resuldo de ft_strtrim:\n%s\n", ft_strtrim(string, x));
}*/
