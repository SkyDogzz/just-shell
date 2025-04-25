/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_postorder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:52:32 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:00:04 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_postorder(t_btree *root, void (*f)(void *))
{
	if (!root)
		return ;
	if (root->left)
		ft_btree_postorder(root->left, f);
	if (root->right)
		ft_btree_postorder(root->right, f);
	f(root->content);
}
