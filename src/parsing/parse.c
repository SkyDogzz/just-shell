/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:12:18 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/25 18:12:52 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*cut_and_get_pipe(t_list **tokens)
{
	t_list	*start;
	t_token	*act_t;
	t_list	*mem;

	start = *tokens;
	*tokens = (*tokens)->next;
	while (*tokens)
	{
		act_t = (*tokens)->content;
		if (ft_is_pipe(act_t))
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
		last = ft_lstlast(pipes)->content;
		token = ft_lstlast(last)->content;
		if (ft_is_pipe(token))
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

static int	cmp(void *c1, void *c2)
{
	t_leaf	*leaf1;
	t_leaf	*leaf2;

	leaf1 = c1;
	leaf2 = c2;
	if (leaf1->type == NODE_PIPE && leaf2->type == NODE_WORD)
		return (0);
	return (1);
}

static char	**args_from_lst(t_list *tokens)
{
	char	**content;
	t_token	*token;
	int		size;
	int		pos;

	size = ft_lstsize(tokens);
	content = (char **)malloc(sizeof(char *) * (size + 1));
	if (!content)
		return (NULL);
	pos = 0;
	while (tokens)
	{
		token = tokens->content;
		content[pos++] = ft_strdup(token->content);
		tokens = tokens->next;
	}
	content[size] = 0;
	return (content);
}

void	ft_fill_tree(t_btree **root, t_list *pipes)
{
	t_list	*tokens;
	t_token	*token;
	t_leaf	*leaf;

	while (pipes)
	{
		tokens = pipes->content;
		token = tokens->content;
		if (ft_lstsize(tokens) == 1 && ft_is_pipe(token))
		{
			leaf = ft_create_leaf(NODE_PIPE, NULL);
			ft_btree_insert_in(root, ft_btree_new(leaf), cmp);
		}
		else
		{
			leaf = ft_create_leaf(NODE_WORD, args_from_lst(tokens));
			ft_btree_insert_in(root, ft_btree_new(leaf), cmp);
		}
		pipes = pipes->next;
	}
	(void) pipes;
	(void) root;
}

t_btree	*ft_parse(t_list *tokens)
{
	t_btree	*root;
	t_list	*pipes;

	pipes = parse_pipe(tokens);
	ft_lstprint_pipes(pipes, "Print pipes");
	root = NULL;
	ft_fill_tree(&root, pipes);
	ft_lstclear(&pipes, ft_lstclear_pipes);
	ft_print_tree(root, 0, 1);
	return (root);
	(void)tokens;
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
