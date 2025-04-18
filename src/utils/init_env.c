/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:58 by yandry            #+#    #+#             */
/*   Updated: 2025/04/18 15:56:36 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(void *env)
{
	free(((t_env *)env)->name);
	free(((t_env *)env)->value);
	free(env);
	env = NULL;
}

static void	ft_free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

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

static t_list	*append_env_node(t_list *env_list, char **split)
{
	char	*name;
	char	*value;
	t_env	*env_node;
	t_list	*node;

	if (!split || !split[0] || !split[1])
		return (NULL);
	name = ft_strdup(split[0]);
	value = ft_strdup(split[1]);
	if (!name || !value)
		return (free(name), free(value), NULL);
	env_node = create_node(name, value);
	if (!env_node)
		return (free(name), free(value), NULL);
	node = ft_lstnew(env_node);
	if (!node)
		return (clear_env(env_node), NULL);
	ft_lstadd_back(&env_list, node);
	return (env_list);
}

t_list	*ft_init_env(const char **env)
{
	t_list	*env_list;
	t_list	*current_node;
	char	**splitted_env;
	int		i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		splitted_env = ft_split(env[i], '=');
		current_node = append_env_node(env_list, splitted_env);
		ft_free_arr(splitted_env);
		if (!current_node)
			return (ft_lstclear(&env_list, clear_env), NULL);
		if (!env_list)
			env_list = current_node;
		i++;
	}
	return (env_list);
}
