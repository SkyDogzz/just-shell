/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:21:19 by yandry            #+#    #+#             */
/*   Updated: 2025/04/23 14:27:35 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "includes/libft.h"
#include "minishell.h"

void	*ft_sombrax(t_list *env, t_btree *tree)
{
	ft_btree_clear(&tree, ft_free_leaf);
	rl_clear_history();
	ft_clear_env(env);
	return (NULL);
}
