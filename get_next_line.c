/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:31:39 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/22 19:15:55 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	if (start >= slen)
		return (ft_strdup(""));
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}

static char	*read_and_store(int fd, char *storage)
{
	char	*buf;
	int		readed;

	readed = 1;
	while(!ft_strchr(storage, '\n') && readed > 0)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
		{
			if (storage)
				free(storage);
			free(buf);
			return (NULL);
		}
		buf[readed] = '\0';
		if (readed == 0)
		{
			free(buf);
			return (storage);
		}
		storage = ft_strjoin(storage, buf);
		free(buf);
	}
	return (storage);
}

static char	*get_line(char *storage)
{
	size_t	i;
	size_t	j;
	char	*line;

	if (!storage)
		return (NULL);
	i = 0;
	j = 0;
	while(storage[i] && storage[i] != '\n')
		i ++;
	if (!i)
		return (storage);
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while(j <= i)
	{
		line[j] = storage[j];
		j ++;
	}
	line[j] = '\0';
	return (line);
}

static char	*clean_storage(char *storage)
{
	size_t	i;
	size_t	len;
	char	*new_storage;

	if (!storage)
		return (NULL);
	len = ft_strlen(storage);
	i = 0;
	while(storage[i] && storage[i] != '\n')
		i ++;
	++ i;
	new_storage = ft_substr(storage, i, (ft_strlen(storage) - i));
	free(storage);
	if (!new_storage)
	{
		return (NULL);
	}
	storage = new_storage;
	return(storage);
}

char *get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
		return (NULL);
	// read from fd and store
	storage = read_and_store(fd, storage);
	if (!storage)
		return (NULL);
	// extract from storage to line
	if (ft_strchr(storage, '\n') || ft_strlen(storage))
	{
		line = get_line(storage);
		if (!line[0])
		{
			free(line);
			free(storage);
			return (NULL);
		}
		// clean storage
		storage = clean_storage(storage);
		if (!storage)
			free(line);
	}
	return (line);
}

//int	main(void)
//{
//	char	*str;
//	int		fd;
//	fd = open("1.txt", O_RDONLY);
//	str = get_next_line(fd);
//	while (str)
//	{
//		printf("%s", str);
//		free(str);
//		str = get_next_line(fd);
//	}
//	//printf("%s", str);
//	free(str);
//	close(fd);
//}