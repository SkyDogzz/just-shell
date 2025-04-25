/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:53:44 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:55:25 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include "ft_utils.h"

typedef struct s_btree
{
	void			*content;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

// tree related functions
void	ft_print_tree(t_btree *root, int level, int is_last);
t_btree	*ft_btree_new(void *content);
void	ft_btree_insert(t_btree **root, t_btree *ne,
			int (*cmp)(void *, void *));
void	ft_btree_insert_in(t_btree **root, t_btree *ne,
			int (*cmp)(void *, void *));
void	ft_btree_inorder(t_btree *root, void (*f)(void *));
void	ft_btree_preorder(t_btree *root, void (*f)(void *));
void	ft_btree_postorder(t_btree *root, void (*f)(void *));
int		ft_btree_size(t_btree *root);
int		ft_btree_height(t_btree *root);
void	ft_btree_clear(t_btree **root, void (*del)(void *));
void	ft_fill_tree(t_btree **root, t_list *pipes);
t_list	*ft_parse_redir(t_list *tokens);

int		ft_exec(t_btree *root, t_list *env);

#endif
