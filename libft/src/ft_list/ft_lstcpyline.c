/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpyline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:45:03 by yandry            #+#    #+#             */
/*   Updated: 2025/02/01 14:55:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstcpyline(t_list *list, void *line)
{
	int	i;
	int	k;

	if (!list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (((char *)list->content)[i])
		{
			if (((char *)list->content)[i] == '\n')
			{
				((char *)line)[k++] = '\n';
				((char *)line)[k] = '\0';
				return ;
			}
			((char *)line)[k++] = ((char *)list->content)[i++];
		}
		list = list->next;
	}
	((char *)line)[k] = '\0';
}
