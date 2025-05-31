/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 06:32:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "minishell.h"
#include <unistd.h>

int	ft_exec(const t_context *const context)
{
	int		ret;
	t_btree	*root;

	if (!context)
		return (1);
	ret = 0;
	root = context->root;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = ft_exec_simple(context);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = ft_exec_pipeline(context);
	else if (((t_leaf *)root->content)->type == NODE_LOGICAL)
		ret = ft_exec_logical(context);
	return (ret);
}
