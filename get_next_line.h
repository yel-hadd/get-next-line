/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:31:47 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/25 13:17:32 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char    *get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strchr(char *s, int c);
void	*ft_memset(void *ptr, int x, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, void *src, size_t n);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif

