/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:26:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 12:24:14 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"

static int	exec_logical_node(t_contex2 *context)
{
	int		left_status;
	int		right_status;
	char	*op;
	t_btree	*mem;

	mem = context->context;
	context->context = mem->left;
	left_status = ft_exec(context);
	op = ((t_leaf *)mem->content)->cmd->args[0];
	if ((ft_strcmp(op, "or") == 0 && left_status != 0)
		|| (ft_strcmp(op, "and") == 0 && left_status == 0))
	{
		context->context = mem->right;
		right_status = ft_exec(context);
		context->context = mem;
		return (right_status);
	}
	context->context = mem;
	return (left_status);
}

int	ft_exec_logical(t_contex2 *context, int *status)
{
	if (!context || !context->context)
		return (0);
	if (((t_leaf *)context->context->content)->type == NODE_LOGICAL)
		*status = exec_logical_node(context);
	return (*status);
}
