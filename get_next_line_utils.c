/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:31:31 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/17 16:27:02 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	slen1;
	size_t	slen2;
	char	*join;

	if ((!s1 && !s2))
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	join = ft_calloc((slen1 + slen2 + 1), sizeof(char));
	if (!join)
	{
		free (s1);
		return (0);
	}
	while (*s1)
		*join ++ = *s1 ++;
	while (*s2)
		*join ++ = *s2 ++;
	return (join - slen1 - slen2);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	s2 = ft_calloc((len + 1), sizeof(char));
	if (!s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		count += 1;
		i ++;
	}
	return (count);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pb;

	pb = (unsigned char *) b;
	while (len != 0)
	{
		*pb = (unsigned char) c;
		pb ++;
		len --;
	}
	return (b);
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