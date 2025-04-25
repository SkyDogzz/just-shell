/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:15:12 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:00:22 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int	ft_btree_size(t_btree *root)
{
	int	size;

	size = 0;
	if (!root)
		return (size);
	size++;
	if (root->left)
		size += ft_btree_size(root->left);
	if (root->right)
		size += ft_btree_size(root->right);
	return (size);
}
