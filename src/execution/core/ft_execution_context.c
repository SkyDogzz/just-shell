/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_context.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:23:32 by yandry            #+#    #+#             */
/*   Updated: 2025/04/26 15:25:04 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_context	*ft_get_execution_context(t_btree *tree, t_list *env)
{
	t_context	*context;

	context = ft_calloc(1, sizeof(t_context));
	if (!context)
		return (NULL);
	context->root = tree;
	context->env = env;
	return (context);
}
