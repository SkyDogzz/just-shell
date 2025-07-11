/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:23:58 by yandry            #+#    #+#             */
/*   Updated: 2025/07/11 15:31:31 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include <stdio.h>

void	ft_update_env(t_list **env, const char *name, const char *newval,
				bool exported)
{
	t_env	*to_update;

	to_update = ft_get_env(*env, name);
	if (to_update)
	{
		free(to_update->value);
		to_update->value = ft_strdup(newval);
		return ;
	}
	ft_new_env(env, name, newval, exported);
}
