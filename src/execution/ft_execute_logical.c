/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_logical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/23 12:03:38 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"

static int	exec_logical_node(t_btree *node, t_list *env)
{
	int	ret;

	ft_exec(node->left, env);
	if (g_exit == 1)
		return (-1);
	if (g_exit != 0 && ft_strcmp(((t_leaf *)node->content)->cmd->args[0], "or")
		== 0)
		ret = ft_exec(node->right, env);
	else if (g_exit == 0 && ft_strcmp(((t_leaf *)node->content)->cmd->args[0],
			"and") == 0)
		ret = ft_exec(node->right, env);
	else
		return (-1);
	return (ret);
}

int	ft_exec_logical(const t_btree *root, t_list *env)
{
	if (!root)
		return (0);
	if (((t_leaf *)root->content)->type == NODE_LOGICAL)
		return (exec_logical_node((t_btree *)root, env));
	return (-1);
}
