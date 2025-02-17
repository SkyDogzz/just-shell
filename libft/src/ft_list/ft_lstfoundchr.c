/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfoundchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:28 by yandry            #+#    #+#             */
/*   Updated: 2024/12/11 13:46:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_lstfoundchr(t_list *list, int c)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (((char *)list->content)[i] && i < BUFFER_SIZE)
		{
			if (((char *)list->content)[i] == c)
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}
