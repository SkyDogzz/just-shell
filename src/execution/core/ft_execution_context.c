/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_context.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:23:32 by yandry            #+#    #+#             */
/*   Updated: 2025/06/30 16:24:37 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_execution.h"

t_context	*ft_get_execution_context(t_btree *tree, t_list **env)
{
	t_context	*context;

	if (!tree || !env)
		return (NULL);
	context = ft_calloc(1, sizeof(*context));
	if (!context)
		return (NULL);
	context->root = tree;
	context->context = tree;
	context->env = *env;
	return (context);
}

void	ft_free_context(t_context *context, bool clear_env)
{
	if (!context)
		return ;
	if (context->root)
		ft_btree_clear(&context->root, ft_free_leaf);
	if (clear_env && context->env)
		ft_clear_env(context->env);
	free(context);
}
