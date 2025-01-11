/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:58:24 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/11 16:12:17 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "lib/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_finalstr(char *buffer);
char	*ft_nextgnl(char *buffer);
char	*ft_search_nl(const char *x, int flag);
char	*ft_chunckjoin(int fd, char *buffer, char *temp);

#endif
