/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:38:37 by yandry            #+#    #+#             */
/*   Updated: 2025/06/27 02:51:45 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "ft_env.h"

/**
 * since exported list points to env_nodes that are still meant to be used after
 * we can't just free those
 * this is 100% a bad design but you gotta understand me
*/
static void	fake_delete(void *env_node)
{
	(void)env_node;
}

static int	handle_no_args(t_list *env)
{
	t_env	*env_node;

	while (env)
	{
		env_node = (t_env *)env->content;
		if (env_node)
			ft_printf("export %s=\"%s\"\n", env_node->name, env_node->value);
		env = env->next;
	}
	return (0);
}

static void	handle_redefine(char *args, t_list *env)
{
	char	**split;
	char	*new;

	split = ft_split(args, '=');
	if (!split)
		return ;
	if (!ft_isalpha(split[0][0]) && split[0][0] != '_')
	{
		ft_dprintf(STDERR_FILENO,
			"ssh-xx: export: %s is not a valid identifier\n", split[0]);
		return ;
	}
	new = ft_strchr(args, '=');
	if (!new)
	{
		ft_free_array((void ***)&split);
		return ;
	}
	ft_update_env(&env, split[0], new + 1, true);
	return (ft_free_array((void ***)&split));
}

int	ft_export(const t_cmd *cmd, t_list *env)
{
	t_list	*exported;
	size_t	i;

	i = 1;
	exported = ft_lstcpy_if(env, is_env_exported, fake_delete);
	if (!cmd->args[i])
		handle_no_args(exported);
	while (cmd->args[i])
		handle_redefine(cmd->args[i++], env);
	ft_lstclear(&exported, fake_delete);
	return (0);
}
