/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:58 by yandry            #+#    #+#             */
/*   Updated: 2025/04/17 17:18:36 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_init_env(const char **env)
{
	t_list	*env_list;
	t_list	*current_node;
	t_env	*env_node;
	char	**splitted_env;
	int		i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		env_node = ft_calloc(1, sizeof(t_env));
		if (!env_node)
			return (NULL);
		splitted_env = ft_split(env[i], '=');
		if (!splitted_env)
			return (NULL);
		env_node->name = splitted_env[0];
		env_node->value = splitted_env[1];
		current_node = ft_lstnew(env_node);
		if (!current_node)
			return (NULL);
		ft_lstadd_back(&env_list, current_node);
		i++;
	}
	return (env_list);
}
