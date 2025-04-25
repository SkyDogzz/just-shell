/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:08:38 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 18:59:45 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_btree_new(void *content)
{
	t_btree	*new;

	if (!content)
		return (NULL);
	new = (t_btree *)malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->content = content;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
