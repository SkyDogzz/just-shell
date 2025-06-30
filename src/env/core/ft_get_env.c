/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:46:56 by yandry            #+#    #+#             */
/*   Updated: 2025/06/30 16:43:19 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

t_env	*ft_get_env(t_list *env, const char *name)
{
	if (!env || !name)
		return (NULL);
	while (env)
	{
		if (is_env(env, name))
			return (((t_env *)env->content));
		env = env->next;
	}
	return (NULL);
}
