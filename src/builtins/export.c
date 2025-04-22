/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:38:37 by yandry            #+#    #+#             */
/*   Updated: 2025/04/22 20:29:56 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "ft_env.h"

/**
 * since exported list points to env_nodes that are still meant to be used after
 * we can't just free those
 * this is 100% a bad design but you gotta understand me
*/
void	fake_delete(void *env_node)
{
	(void)env_node;
}

static t_env	*find_env(const char *env_name, t_list *env)
{
	t_env	*candidate;

	candidate = NULL;
	while (env)
	{
		if (((t_env *)env->content)
			&& ft_strncmp(env_name,
				((t_env *)env->content)->name,
				ft_strlen(env_name)) == 0)
			candidate = (t_env *)env->content;
		env = env->next;
	}
	ft_lstclear(&env, fake_delete);
	return (candidate);
}

static int	handle_no_args(t_list *env)
{
	t_env	*env_node;

	while (env)
	{
		env_node = (t_env *)env->content;
		if (env_node)
			ft_printf("%s=%s\n", env_node->name, env_node->value);
		env = env->next;
	}
	return (0);
}

int	ft_export(const t_cmd *cmd, t_list *env)
{
	t_list	*exported;
	t_env	*env_node;
	size_t	i;

	i = 1;
	exported = ft_lstcpy_if(env, is_env_exported, clear_env);
	if (!cmd->args[i])
		handle_no_args(exported);
	while (cmd->args[i])
	{
		env_node = find_env(cmd->args[i], exported);
		if (env_node)
			ft_printf("%s=%s\n", env_node->name, env_node->value);
		i++;
	}
	ft_lstclear(&exported, fake_delete);
	return (0);
}
