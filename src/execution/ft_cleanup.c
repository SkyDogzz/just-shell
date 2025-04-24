/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:46:23 by skydogzz          #+#    #+#             */
/*   Updated: 2025/04/24 20:49:53 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

static void	del(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->name);
	free(env->value);
	free(env);
}

void	ft_cleanup(t_list *env, t_btree *root)
{
	ft_lstclear(&env, del);
	ft_btree_clear(&root, ft_free_leaf);
	free(env);
	free(root);
}
