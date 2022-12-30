/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:31:39 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/25 17:38:58 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			tst_overflow;
	size_t			i;

	i = 0;
	if (!size || !count)
		return (NULL);
	tst_overflow = count * size;
	if (tst_overflow != 0 && tst_overflow / size != count)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	while (i < size)
		p[i ++] = 0;
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	slen1;
	size_t	slen2;
	char	*join;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	join = malloc((slen1 + slen2 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	while (*s1)
		*join ++ = *s1 ++;
	while (*s2)
		*join ++ = *s2 ++;
	*join = '\0';
	return (join - slen1 - slen2);
}

int	get_line_index(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	read_and_save(char **storage, int fd)
{
	char	*buf;
	long	read_byte;
	long	i;
	char	*tmp;

	read_byte = 1;
	i = 0;
	while (!ft_strchr(*storage, '\n'))
	{
		buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		if (!buf)
			return (free(*storage));
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
			return (free(*storage), free(buf));
		if (read_byte == 0)
			return (free(buf));
		tmp = *storage;
		*storage = ft_strjoin(*storage, buf);
		free(buf);
		free(tmp);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;
	char		*tmp;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_save(&storage, fd);
	if (!storage || !*storage)
		return (free(storage), NULL);
	i = get_line_index(storage);
	line = ft_substr(storage, 0, i);
	if (!line)
		return (free(storage), NULL);
	tmp = storage;
	storage = ft_substr(storage, i, ft_strlen(storage) - i);
	free(tmp);
	return (line);
}
