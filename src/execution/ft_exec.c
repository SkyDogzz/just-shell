/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/04/25 19:04:27 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int	ft_exec(t_btree	*root, t_list *env)
{
	int	ret;

	ret = 0;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = ft_exec_simple(root, env);
	else if (((t_leaf *)root->content)->type == NODE_LOGICAL)
		ret = ft_exec_logical(root, env);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = ft_exec_pipeline(root, env, STDIN_FILENO);
	return (ret);
}
