/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:31:31 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/22 21:57:48 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	tst_overflow;

	tst_overflow = count * size;
	if (tst_overflow != 0 && tst_overflow / size != count)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	s2 = ft_calloc((ft_strlen((char *)s1) + 1), sizeof(char));
	if (!s2)
		return (NULL);
	i = -1;
	while (s1[++i])
	{
		s2[i] = s1[i];
	}
	return (s2);
}

void	*ft_memset(void *ptr, int x, size_t n)
{
	char	*str;

	str = ptr;
	while (n--)
	{
		*str++ = (unsigned char)x;
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		count += 1;
		i ++;
	}
	return (count);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if(!s)
		return (NULL);
	if ((char) c == '\0')
		return (&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (&s[i]);
		i ++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*dstcpy;

	dstcpy = dst;
	if (!dst && !src)
		return (dstcpy);
	while ((n > 0))
	{
		*(char *)dst ++ = *(char *)src ++;
		n --;
	}
	return (dstcpy);
}