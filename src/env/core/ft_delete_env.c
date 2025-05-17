/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:44:00 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 18:06:45 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

void	ft_delete_env(t_list **env, const char *name)
{
	t_list	*current;
	t_list	*env_prev;

	if (!env || !*env || !ft_get_env(*env, name))
		return ;
	current = *env;
	env_prev = NULL;
	while (current)
	{
		if (is_env(current, name))
		{
			if (!env_prev)
				*env = current->next;
			else
				env_prev->next = current->next;
			ft_lstdelone(current, clear_env);
			return ;
		}
		env_prev = current;
		current = current->next;
	}
}
