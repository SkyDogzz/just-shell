/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:12:18 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/10 20:19:47 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_btree	*ft_parse(t_list *tokens)
{
	t_btree	*root;

	root = ft_btree_new(ft_create_leaf(1,
				ft_split("first", ' ')));
	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(2,
				ft_split("second", ' '))), ft_cmp_leaf);
	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(3,
				ft_split("third", ' '))), ft_cmp_leaf);
	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,
				ft_split("fourth", ' '))), ft_cmp_leaf);
	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,
				ft_split("fifth", ' '))), ft_cmp_leaf);
	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,
				ft_split("sixth", ' '))), ft_cmp_leaf);
	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,
				ft_split("seventh", ' '))), ft_cmp_leaf);
	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,
				ft_split("eigth", ' '))), ft_cmp_leaf);
	/*ft_print_tree(root, 0, 0);*/
	return (root);
	(void) tokens;
}
