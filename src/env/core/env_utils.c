/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:03:39 by yandry            #+#    #+#             */
/*   Updated: 2025/06/29 01:13:25 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

inline bool	is_env(t_list *node, const char *name)
{
	return (ft_strncmp(((t_env *)node->content)->name,
			name,
			ft_strlen(name) + 1) == 0);
}

bool	is_env_exported(t_list *env)
{
	t_env	*env_node;

	env_node = (t_env *)env->content;
	return (env_node && env_node->exported);
}

void	*copy_env_to_str(const void *env)
{
	char	*env_str;
	char	*str;

	str = ft_strjoin(((t_env *)env)->name, "=");
	if (!str)
		return (NULL);
	if (!((t_env *)env)->value)
		env_str = ft_strjoin(str, "");
	else
		env_str = ft_strjoin(str, ((t_env *)env)->value);
	free(str);
	return (env_str);
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
