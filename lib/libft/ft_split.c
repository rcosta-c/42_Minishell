/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:33:03 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/24 14:04:14 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	words;

	if (!s)
		return (0);
	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (words);
}

static char	*ft_extract_word(const char *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static void	*free_arrstr(char **arrstr)
{
	int	x;

	x = 0;
	while (arrstr[x])
		free(arrstr[x++]);
	free(arrstr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arrstr;
	size_t	words;
	size_t	i;

	words = ft_countwords(s, c);
	arrstr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arrstr || !s || (!arrstr && !s))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			arrstr[i] = ft_extract_word(s, c);
			if (!arrstr[i])
				return (free_arrstr(arrstr));
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	arrstr[i] = NULL;
	return (arrstr);
}

/*
int     main()
{
	char	*s = "*Hello*the*re*,dude!";
	char	**x = ft_split(s, '*');

	while (*x)
		printf("%s\n", *x++);
}*/
