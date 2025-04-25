/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_inorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:46:31 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 18:59:29 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_inorder(t_btree *root, void (*f)(void *))
{
	if (!root)
		return ;
	if (root->left)
		ft_btree_inorder(root->left, f);
	f(root->content);
	if (root->right)
		ft_btree_inorder(root->right, f);
}
