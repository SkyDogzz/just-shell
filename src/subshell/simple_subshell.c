/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 05:16:59 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/12 16:14:19 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"

static bool	handle_subshell_utils(t_leaf *leaf, t_btree **root, t_list *env,
		t_list *tokens)
{
	t_btree		*mem ;
	t_context	*context;
	char		*sub;

	sub = ft_substr(leaf->cmd->args[0], 1, ft_strlen(leaf->cmd->args[0]) - 4);
	tokens = ft_lex(env, sub);
	free(sub);
	if (!tokens)
		return (true);
	if (!ft_findsubshell(env, &tokens))
	{
		ft_putendl_fd("Syntax error near unexpected token ')", STDERR_FILENO);
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (false);
	}
	context = ft_get_execution_context(ft_parse(tokens), env);
	mem = *root;
	*root = context->root;
	free(context);
	ft_btree_clear(&mem, ft_free_leaf);
	if (!handle_subshell_simple(root, tokens, env))
		return (false);
	return (true);
}

static bool	verif(t_leaf *leaf)
{
	return (leaf->type == NODE_WORD && leaf->cmd && leaf->cmd->args
		&& leaf->cmd->args[0] && leaf->cmd->args[0][0]
		&& leaf->cmd->args[0][0] == '(');
}

bool	handle_subshell_simple(t_btree **root, t_list *tokens, t_list *env)
{
	t_leaf	*leaf;

	if (!root)
		return (false);
	leaf = (*root)->content;
	if (verif(leaf))
		if (!handle_subshell_utils(leaf, root, env, tokens))
			return (false);
	if ((*root)->left)
	{
		leaf = (*root)->left->content;
		if (verif(leaf))
			if (!handle_subshell_utils(leaf, &(*root)->left, env, tokens))
				return (false);
	}
	if ((*root)->right)
	{
		leaf = (*root)->right->content;
		if (verif(leaf))
			if (!handle_subshell_utils(leaf, &(*root)->right, env, tokens))
				return (false);
	}
	return (true);
}
