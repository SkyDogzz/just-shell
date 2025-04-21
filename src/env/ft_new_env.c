/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:08:13 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 16:57:50 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

static t_env	*create_node(char *name, char *value)
{
	t_env	*env_node;

	env_node = ft_calloc(1, sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->name = name;
	env_node->value = value;
	return (env_node);
}

static t_list	*spawn_env_node(const char *name, const char *value)
{
	t_env	*env_node;
	t_list	*node;
	char	*env_name;
	char	*env_value;

	if (!name || !value)
		return (NULL);
	env_name = ft_strdup(name);
	env_value = ft_strdup(value);
	if (!env_name || !env_value)
		return (free(env_name), free(env_value), NULL);
	env_node = create_node(env_name, env_value);
	if (!env_node)
		return (NULL);
	node = ft_lstnew(env_node);
	if (!node)
		return (free(env_node->name),
			free(env_node->value), free(env_node), NULL);
	return (node);
}

void	ft_new_env(t_list **env, const char *name, const char *value)
{
	t_list	*new_node;

	new_node = spawn_env_node(name, value);
	if (!new_node)
		return ;
	ft_lstadd_back(env, new_node);
}
