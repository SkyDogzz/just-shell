/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:03:39 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 18:05:22 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

inline bool	is_env(t_list *node, const char *name)
{
	return (ft_strncmp(((t_env *)node->content)->name,
			name,
			ft_strlen(name)) == 0);
}

void	clear_env(void *env)
{
	t_env	*env_t;

	env_t = (t_env *)env;
	if (!env_t)
		return ;
	free(((t_env *)env)->name);
	free(((t_env *)env)->value);
	free(env);
	env = NULL;
}
