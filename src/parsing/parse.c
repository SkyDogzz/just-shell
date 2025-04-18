/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:12:18 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/15 15:07:20 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*cut_and_get_pipe(t_list **tokens)
{
	t_list	*start;
	t_token	*act_t;
	t_list	*mem;

	start = *tokens;
	while (*tokens)
	{
		act_t = (t_token *)(*tokens)->content;
		if (ft_is_pipe(act_t) || ft_is_logical(act_t))
		{
			mem = (*tokens)->next;
			(*tokens)->next = NULL;
			(*tokens) = mem;
			break ;
		}
		*tokens = (*tokens)->next;
	}
	return (start);
}

static t_list	*parse_pipe(t_list *tokens)
{
	t_list	*pipes;
	t_list	*last;
	t_token	*token;
	t_list	*pre;

	pipes = NULL;
	while (tokens)
	{
		ft_lstadd_back(&pipes, ft_lstnew(cut_and_get_pipe(&tokens)));
		last = (t_list *)ft_lstlast(pipes)->content;
		token = (t_token *)ft_lstlast(last)->content;
		if (ft_is_pipe(token) || ft_is_logical(token))
		{
			pre = last;
			while (pre && pre->next && pre->next->next)
				pre = pre->next;
			ft_lstadd_back(&pipes, ft_lstnew(pre->next));
			pre->next = NULL;
		}
	}
	return (pipes);
}

t_btree	*ft_parse(t_list *tokens)
{
	t_btree	*root;
	t_list	*pipes;

	pipes = parse_pipe(tokens);
	root = NULL;
	ft_fill_tree(&root, pipes);
	ft_lstclear(&pipes, ft_lstclear_pipes);
	return (root);
}

/*t_btree	*ft_parse(t_list *tokens)*/
/*{*/
/*	t_btree	*root;*/
/**/
/*	root = ft_btree_new(ft_create_leaf(1,*/
/*				ft_split("first", ' ')));*/
/*	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(2,*/
/*				ft_split("second", ' '))), ft_cmp_leaf);*/
/*	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(3,*/
/*				ft_split("third", ' '))), ft_cmp_leaf);*/
/*	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,*/
/*				ft_split("fourth", ' '))), ft_cmp_leaf);*/
/*	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,*/
/*				ft_split("fifth", ' '))), ft_cmp_leaf);*/
/*	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,*/
/*				ft_split("sixth", ' '))), ft_cmp_leaf);*/
/*	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,*/
/*				ft_split("seventh", ' '))), ft_cmp_leaf);*/
/*	ft_btree_insert(&root, ft_btree_new(ft_create_leaf(0,*/
/*				ft_split("eigth", ' '))), ft_cmp_leaf);*/
/*	ft_print_tree(root, 0, 0);*/
/*	return (root);*/
/*	(void) tokens;*/
/*}*/
