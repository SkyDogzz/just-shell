/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:50:10 by yandry            #+#    #+#             */
/*   Updated: 2025/04/14 18:43:16 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	flush_list(t_list **list, t_list *clean, char *buffer)
{
	t_list	*next;

	if (!*list)
	{
		if (((char *)clean->content)[0])
			*list = clean;
		else
		{
			free(buffer);
			free(clean);
		}
		return ;
	}
	next = (*list)->next;
	free((*list)->content);
	free(*list);
	*list = next;
	flush_list(list, clean, buffer);
}

static void	clear_list(t_list **list)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		k;
	char	*buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return ;
	clean = (t_list *)malloc(sizeof(t_list));
	if (!clean)
		return (free(buff));
	last = ft_lstlast(*list);
	i = 0;
	k = 0;
	while (((char *)last->content)[i] && ((char *)last->content)[i] != '\n')
		++i;
	while (((char *)last->content)[i] && ((char *)last->content)[++i])
		buff[k++] = ((char *)last->content)[i];
	buff[k] = '\0';
	clean->content = buff;
	clean->next = NULL;
	flush_list(list, clean, buff);
}

static char	*retrieve_line(t_list *list)
{
	int		len;
	char	*line;

	if (!list)
		return (NULL);
	len = ft_lstlentochr(list, '\n');
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	ft_lstcpyline(list, line);
	return (line);
}

static void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buff;

	while (!ft_lstfoundchr(*list, '\n'))
	{
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		char_read = read(fd, buff, BUFFER_SIZE);
		if (!char_read)
		{
			free(buff);
			return ;
		}
		buff[char_read] = '\0';
		ft_lstadd_back(list, ft_lstnew(buff));
	}
}

char	*ft_get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = retrieve_line(list);
	clear_list(&list);
	return (next_line);
}
