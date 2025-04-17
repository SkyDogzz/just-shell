/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:58 by yandry            #+#    #+#             */
/*   Updated: 2025/04/17 18:34:15 by yandry           ###   ########.fr       */
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

static void	*ft_clean_failed_env(t_list **env, t_env *env_node)
{
	ft_lstclear(env, clear_env);
	if (env_node)
		clear_env(env_node);
	return (NULL);
}

static void	ft_free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static bool	init_env_node(t_env **env, char **split)
{
	*env = ft_calloc(1, sizeof(t_env));
	if (!*env)
		return (false);
	(*env)->name = ft_strdup(split[0]);
	if (!(*env)->name)
	{
		free(*env);
		*env = NULL;
		return (false);
	}
	(*env)->value = ft_strdup(split[1]);
	if (!(*env)->value)
	{
		free((*env)->name);
		free(*env);
		*env = NULL;
		return (false);
	}
	ft_free_arr(split);
	return (true);
}

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
		splitted_env = ft_split(env[i], '=');
		if (!splitted_env || !splitted_env[0] || !splitted_env[1])
			return (ft_free_arr(splitted_env),
				ft_lstclear(&env_list, clear_env), NULL);
		if (!init_env_node(&env_node, splitted_env))
			return (ft_clean_failed_env(&env_list, env_node));
		current_node = ft_lstnew(env_node);
		if (!current_node)
			return (ft_clean_failed_env(&env_list, env_node));
		ft_lstadd_back(&env_list, current_node);
		i++;
	}
	return (env_list);
}
