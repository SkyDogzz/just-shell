/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:12:18 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/05 16:38:59 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_logical(t_token *token)
{
	if (token->token_type != T_OPERATOR_M)
		return (false);
	if (ft_strcmp(token->content, "||") == 0 || ft_strcmp(token->content, "&&") == 0)
		return (true);
	return (false);
}

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

static int	cmp(void *c1, void *c2)
{
	t_leaf	*leaf1;
	t_leaf	*leaf2;

	leaf1 = (t_leaf *)c1;
	leaf2 = (t_leaf *)c2;
	if (leaf1->type == NODE_PIPE && leaf2->type == NODE_WORD)
		return (0);
	if (leaf1->type == NODE_LOGICAL && leaf2->type == NODE_WORD)
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
		token = (t_token *)tokens->content;
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
		tokens = (t_list *)pipes->content;
		if (!tokens)
		{
			pipes = pipes->next;
			continue ;
		}
		token = tokens->content;
		if (ft_lstsize(tokens) == 1 && ft_is_pipe(token))
		{
			leaf = ft_create_leaf(NODE_PIPE, NULL);
			ft_btree_insert_in(root, ft_btree_new(leaf), cmp);
		}
		else if (ft_lstsize(tokens) == 1 && ft_is_logical(token))
		{
			if (ft_strcmp(token->content, "||") == 0)
				leaf = ft_create_leaf(NODE_LOGICAL, ft_split("or", 0));
			else
				leaf = ft_create_leaf(NODE_LOGICAL, ft_split("and", 0));
			ft_btree_insert_in(root, ft_btree_new(leaf), cmp);
		}
		else
		{
			leaf = ft_create_leaf(NODE_WORD, args_from_lst(tokens));
			ft_btree_insert_in(root, ft_btree_new(leaf), cmp);
		}
		pipes = pipes->next;
	}
}

t_btree	*ft_parse(t_list *tokens)
{
	t_btree	*root;
	t_list	*pipes;

	//ft_lstprint_tokens(tokens, "Print tokens");
	pipes = parse_pipe(tokens);
	//ft_lstprint_pipes(pipes, "Print pipes");
	root = NULL;
	ft_fill_tree(&root, pipes);
	ft_lstclear(&pipes, ft_lstclear_pipes);
	//ft_print_tree(root, 0, 1);
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
