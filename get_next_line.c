/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:31:39 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/17 16:29:01 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_nl(char *stockage)
{
	size_t	len;
	char	*new_stockage;
	size_t	j;
	size_t	i;

	if (!stockage)
		return (NULL);
	i = 0;
	while (stockage[i] != '\n' && stockage[i])
		i ++;
	j = 0;
	len = ft_strlen(stockage);
	new_stockage = ft_calloc((len - i + 1), sizeof(char));
	if (!new_stockage)
	{
		free(stockage);
		return (NULL);
	}
	while (stockage[i])
		new_stockage[j ++] = stockage[++i];
	free(stockage);
	return (new_stockage);
}

static char	*return_line(char	*stockage)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stockage)
		return (NULL);
	while (stockage[i] != '\n' && stockage[i])
		i ++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
	{
		free(stockage);
		return (NULL);
	}
	i = 0;
	while (stockage[i] != '\n' && stockage[i])
	{
		line[i] = stockage[i];
		i ++;
	}
	line[i] = stockage[i];
	return (line);
}

char *get_next_line(int fd)
{
	static char	*stockage;
	char		*buff;
	long long	read_bytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		if (stockage)
			free(stockage);
		return (NULL);
	}
	read_bytes = 1;
	while(read_bytes && !ft_strchr(stockage, '\n'))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			if (stockage)
				free (stockage);
			free(buff);
			return (NULL);
		}
		else if (read_bytes == 0)
			break ;
		buff[read_bytes] = '\0';
		stockage = ft_strjoin(stockage, buff);
	}
	free(buff);
	line = return_line(stockage);
	if (!line || !line[0])
	{
		if (stockage)
			free(stockage);
		if (line)
			free(line);
		return (NULL);
	}
	stockage = clean_nl(stockage);
	if (!stockage)
	{
		if (line)
			free(line);
		return (NULL);
	}
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
// 		sleep(1);
// 	}
// 	close(fd);
// }