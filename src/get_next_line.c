/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:57:56 by yel-hadd          #+#    #+#             */
/*   Updated: 2022/12/13 15:19:30 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gen_line(char **ligne, t_list *node)
{
	int	i;
	int	j;

	j = 0;
	while(node)
	{
		i = 0;
		while(node->content[i])
		{
			if (node->content[i] == '\n')
			{
				j ++;
				break ;
			}
			j ++;
			i ++;
		}
		node = node->next;
	}
	*ligne = malloc(sizeof(char) * (j + 1));
}

void	ext_line(t_list *node, char **ligne)
{
	int	i;
	int	j;

	if (!node)
		return ;
	gen_line(ligne, node);
	if (!*ligne)
		return;
	j = 0;
	while (node)
	{
		i = 0;
		while (node->content[i])
		{
			if (node->content[i] == '\n')
			{
				(*ligne)[j ++] = node->content[i];
				break;
			}
			i ++;
		}
		node = node->next;
	}
}

void	store(t_list **storage, char *buf, int lu)
{
	int		i;
	t_list	*last;
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
	if (!*storage)
	{
		ft_lstadd_back(storage, new);
		return ;
	}
	else
		ft_lstadd_back(storage, new);
	last = ft_lstlast(*storage);
	last->next = new;
}

void	read_to_storage(int fd, t_list **storage, int *lu_ptr)
{
	char	*buf;

	while (!nl_exists(*storage) && *lu_ptr > 0)
	{
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char) );
		if (!buf)
			return ;
		*lu_ptr = (int) read(fd, buf, BUFFER_SIZE);
		if (!*storage || *lu_ptr < 0)
		{
			free(buf);
			return ;
		}
		buf[*lu_ptr] = '\0';
		store(storage, buf, *lu_ptr);
		free(buf);
	}
}

void	free_storage(t_list *storage)
{
	t_list	*temp;
	t_list	*next;

	temp = storage;
	while(temp)
	{
		free(temp->content);
		next = temp ->next;
		free(temp);
		temp = next;
	}
}

void	clean_storage(t_list **storage)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if(!storage || !clean_node)
		return ;
	last = ft_lstlast(*storage);
	i = 0;
	j = 0;
	while((last->content[i]) && (last->content[i] != '\n'))
		i ++;
	if (last->content && last->content[i] == '\n')
		i ++;
	clean_node->content = malloc(sizeof(char) * (ft_strlen(&last->content[i]) + 1));
	if (!clean_node->content)
		return ;
	while (last->content[i])
		clean_node->content[j ++] = last->content[i ++];
	clean_node->content[j] = '\0';
	free_storage(*storage);
	*storage = clean_node;
}

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
	ext_line(storage, &ligne);
	// 3. clean up stash
	clean_storage(&storage);
	if (!ligne[0])
	{
		free_storage(storage);
		storage = NULL;
		free(ligne);
		return (NULL);
	}
	return (ligne);
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