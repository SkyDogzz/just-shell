/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:37:56 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 18:59:40 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_insert_in(t_btree **root, t_btree *ne,
			int (*cmp)(void *, void *))
{
	t_btree	*mem;

	if (!root || !ne)
		return ;
	if (!*root)
	{
		*root = ne;
		return ;
	}
	if (cmp(ne->content, (*root)->content) < 0)
		ft_btree_insert_in(&(*root)->left, ne, cmp);
	else if (cmp(ne->content, (*root)->content) > 0)
		ft_btree_insert_in(&(*root)->right, ne, cmp);
	else
	{
		mem = *root;
		*root = ne;
		(*root)->left = mem;
	}
}
