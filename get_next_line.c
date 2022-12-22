/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:31:39 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/22 23:08:35 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	tlen;
	char	*js;
	int		i;
	int		j;

	tlen = 0;
	if (!s1)
		return (ft_strdup(s2));
	tlen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	if (tlen)
		tlen ++;
	js = ft_calloc((int)tlen, sizeof(char));
	if (!js)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		js[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		js[i++] = s2[j++];
	free(s1);
	return (js);
}

char	*update_storage(char *storage)
{
	char	*new_storage;
	long	i;
	long	j;

	j = 0;
	i = 0;
	while (storage[j] && storage[j] != '\n')
		j ++;
	new_storage = ft_calloc((ft_strlen(storage) - j), sizeof(char));
	if (!new_storage)
		return (NULL);
	j ++;
	while(storage[j])
		new_storage[i ++] = storage[j ++];
	return (new_storage);
}

char	*get_line(char *storage)
{
	char	*line;
	long	i;

	// if (!ft_strchr(storage, '\n') && ft_strlen(storage))
	// 	return (ft_strdup(storage));
	i = 0;
	line = NULL;
	if (!storage[0] || !storage)
		return (NULL);
	while(storage[i] != '\n' && storage[i])
		i ++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while(storage[i] != '\n' && storage[i])
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = storage[i];
	return (line);
}

char *read_and_save(char *storage, int fd)
{
	char	*buf;
	long	read_byte;
	long	i;

	read_byte = 1;
	i = 0;
	buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (read_byte && !ft_strchr(storage, '\n'))
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if(read_byte == -1)
		{
			free (buf);
			return (NULL);
		}
		if (read_byte == 0)
			break;
		storage = ft_strjoin(storage, buf);
	}
	free(buf);
	return (storage);
}

char *get_next_line(int fd)
{
	char		*line;
	static char	*storage;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_and_save(storage, fd);
	if (!storage || !storage[0])
	{
		free(storage);
		return (NULL);
	}
	line = get_line(storage);
	if (!line)
	{
		free(storage);
		return (NULL);
	}
	tmp = update_storage(storage);
	free(storage);
	storage = tmp;
	return (line);
}

// int	main(void)
// {
// 	char	*str;
// 	int		fd;
// 	fd = open("1.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	close(fd);
// }