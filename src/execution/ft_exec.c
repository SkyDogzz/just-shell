/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/04/26 18:56:15 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int	ft_exec(t_context *context)
{
	int		ret;
	t_btree	*root;
	t_list	*env;

	if (!context)
		return (1);
	ret = 0;
	root = context->root;
	env = context->env;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = ft_exec_simple(root, env);
	return (ret);
}
