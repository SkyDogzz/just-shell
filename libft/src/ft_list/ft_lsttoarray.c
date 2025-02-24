/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:42:01 by yandry            #+#    #+#             */
/*   Updated: 2025/02/01 14:18:14 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_errorcleanup(void **array, int index)
{
	while (--index >= 0)
		free(array[index]);
	free(array);
	return (NULL);
}

void	**ft_lsttoarray_s(t_list *lst, const ssize_t elem_size)
{
	t_list	*list;
	void	**dest;
	int		i;

	if (!lst && elem_size < 1)
		return (NULL);
	dest = NULL;
	i = 0;
	list = lst;
	dest = (void **)malloc(sizeof(void *) * (ft_lstsize(list) + 1));
	if (!dest)
		return (NULL);
	while (list)
	{
		dest[i] = malloc(elem_size);
		if (!dest[i])
			return (ft_errorcleanup(dest, i));
		ft_memcpy(dest[i], list->content, elem_size);
		list = list->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	**ft_lsttoarray_c(t_list *lst, void *(*copy_func)(const void *))
{
	t_list	*list;
	void	**dest;
	int		i;

	if (!lst && !copy_func)
		return (NULL);
	dest = NULL;
	i = 0;
	list = lst;
	dest = (void **)malloc(sizeof(void *) * (ft_lstsize(list) + 1));
	if (!dest)
		return (NULL);
	while (list)
	{
		dest[i] = copy_func(list->content);
		if (!dest[i])
			return (ft_errorcleanup(dest, i));
		list = list->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
