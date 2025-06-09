/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/06/09 18:22:20 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "minishell.h"
#include <unistd.h>

static int	ft_exec_simple(t_context *context)
{
	printf("Exec simple commands\n");
	return (0);
	(void) context;
}

static int	ft_exec_pipeline(t_context *context)
{
	printf("Exec pipeline\n");
	return (0);
	(void) context;
}

static int	ft_exec_logical(t_context *context)
{
	printf("Exec logical\n");
	return (0);
	(void) context;
}

int	ft_exec(t_context *context)
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
