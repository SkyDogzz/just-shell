/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:53:09 by yandry            #+#    #+#             */
/*   Updated: 2025/04/23 14:08:35 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "ft_env.h"

static void	fake_delete(void *env_node)
{
	(void)env_node;
}

int	ft_env(const t_cmd *cmd, t_list *env)
{
	t_list	*exported;
	t_env	*env_node;

	(void)cmd;
	exported = ft_lstcpy_if(env, is_env_exported, fake_delete);
	while (exported)
	{
		env_node = (t_env *)exported->content;
		if (env_node)
			ft_printf("%s=%s\n", env_node->name, env_node->value);
		exported = exported->next;
	}
	ft_lstclear(&exported, fake_delete);
	return (0);
}
