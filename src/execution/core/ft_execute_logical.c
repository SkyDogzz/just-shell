/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_logical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/26 16:54:42 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

static int	exec_logical_node(t_btree *node, t_list *env)
{
	int			ret;
	t_context	*context_left;
	t_context	*context_right;

	context_left = ft_get_execution_context(node->left, env);
	context_right = ft_get_execution_context(node->right, env);
	ft_exec(context_left);
	if (g_exit == 1)
		return (-1);
	if (g_exit != 0 && ft_strcmp(((t_leaf *)node->content)->cmd->args[0], "or")
		== 0)
		ret = ft_exec(context_right);
	else if (g_exit == 0 && ft_strcmp(((t_leaf *)node->content)->cmd->args[0],
			"and") == 0)
		ret = ft_exec(context_right);
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
