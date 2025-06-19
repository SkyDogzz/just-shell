/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:26:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 03:10:55 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"

static int	exec_logical_node(t_btree *node, t_list *env)
{
	int			ret;
	int			node_ret;
	t_context	*context_left;
	t_context	*context_right;

	context_left = ft_get_execution_context(node->left, env);
	context_right = ft_get_execution_context(node->right, env);
	node_ret = ft_exec(context_left, true);
	free(context_left);
	if (node_ret == 1)
		return (ft_free_context(context_right, false), -1);
	if (node_ret != 0
		&& ft_strcmp(((t_leaf *)node->content)->cmd->args[0], "or") == 0)
		ret = ft_exec(context_right, true);
	else if (node_ret == 0 && ft_strcmp(((t_leaf *)node->content)->cmd->args[0],
			"and") == 0)
		ret = ft_exec(context_right, true);
	else
		return (free(context_right), -1);
	return (free(context_right), ret);
}

int	ft_exec_logical(t_context *context, int *status)
{
	if (!context || !context->root)
		return (0);
	if (((t_leaf *)context->root->content)->type == NODE_LOGICAL)
		*status = exec_logical_node((t_btree *)context->root, context->env);
	return (*status);
}
