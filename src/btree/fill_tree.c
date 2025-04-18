/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:05:44 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/15 15:14:16 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	ft_choice(t_list *tokens, t_token *token, t_btree **root )
{
	t_leaf	*leaf;

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
}

void	ft_fill_tree(t_btree **root, t_list *pipes)
{
	t_list	*tokens;
	t_token	*token;

	while (pipes)
	{
		tokens = (t_list *)pipes->content;
		if (!tokens)
		{
			pipes = pipes->next;
			continue ;
		}
		token = tokens->content;
		ft_choice(tokens, token, root);
		pipes = pipes->next;
	}
}
