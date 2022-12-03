/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:57:56 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/03 19:33:02 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*storage;
	char			*ligne;
	int				lu;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, ligne, 0) < 0)
		return (NULL);
	lu = 1;
	ligne = NULL;
	// 1. read from fd to storage
	read_to_storage(fd, &storage, &lu);
	if (!storage)
		return (NULL);
	// 2. extract from stash to line
	// 3. clean up stash
	return (ligne);
}


void	store(t_list **storage, char *buf, int lu)
{
	int		i;
	t_list	*current;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (lu + 1));
	if (!new->content)
		return;
	i = 0;
	while (buf[i] && i < lu)
	{
		new->content[i] = buf[i];
		i ++;
	}
	new->content[i] = '\0';
	ft_lstadd_back(storage, new);
}

void	read_to_storage(int fd, t_list **storage, int *lu_ptr)
{
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char) );
	if (!buf)
		return ;
	while (!nl_exists(*storage) && *lu_ptr > 0)
	{
		*lu_ptr = (int) read(fd, buf, BUFFER_SIZE);
		if (!*storage || *lu_ptr < 0)
		{
			free(buf);
			return ;
		}
		buf[*lu_ptr] = '\0';
		store()
	}
}

int	main()
{
	int	fd;
	char	*line;

	fd = open("1.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		if (!line)
			break;
		free(line);
	}
	return (0);
}

/*
- read n bytes from the fd using read()
- store the read bytes in a static string
- check the static string for \n
	- if found:
		- allocate memory for the text until \n
		- free allocated memory
	- if not found
		- read the next n bytes
*/