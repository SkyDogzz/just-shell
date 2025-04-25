/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:59:49 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 18:59:34 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_insert(t_btree **root, t_btree *ne,
			int (*cmp)(void *, void *))
{
	if (!root || !ne)
		return ;
	if (!*root)
	{
		*root = ne;
		return ;
	}
	if (cmp(ne->content, (*root)->content) < 0)
		ft_btree_insert(&(*root)->left, ne, cmp);
	else
		ft_btree_insert(&(*root)->right, ne, cmp);
}
