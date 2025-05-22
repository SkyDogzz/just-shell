/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/05/18 20:55:57 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "minishell.h"
#include <unistd.h>

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
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = ft_exec_pipeline(root, env, STDIN_FILENO);
	else if (((t_leaf *)root->content)->type == NODE_LOGICAL)
		ret = ft_exec_logical(root, env);
	return (ret);
}
