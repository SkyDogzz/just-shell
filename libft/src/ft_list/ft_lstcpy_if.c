/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:41:07 by yandry            #+#    #+#             */
/*   Updated: 2025/04/22 18:51:29 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

t_list	*ft_lstcpy_if(t_list *old_list,
					bool (*condition)(t_list *),
					void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;

	new_list = NULL;
	while (old_list)
	{
		if (condition(old_list))
		{
			current = ft_lstnew(old_list->content);
			if (!current)
			{
				ft_lstclear(&new_list, del);
				return (NULL);
			}
			ft_lstadd_back(&new_list, current);
		}
		old_list = old_list->next;
	}
	return (new_list);
}
