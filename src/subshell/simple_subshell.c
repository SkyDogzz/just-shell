/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 05:16:59 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/03 14:47:25 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"

static bool	handle_subshell_utils(t_btree **root, t_list *env, t_list *tokens,
		int *status)
{
	t_btree		*mem ;
	t_context	*context;
	char		*sub;

	sub = ft_substr(((t_leaf *)(*root)->content)->cmd->args[0], 1,
			ft_strlen(((t_leaf *)(*root)->content)->cmd->args[0]) - 4);
	tokens = ft_lex(env, sub, status);
	free(sub);
	if (!tokens)
		return (true);
	if (!ft_findsubshell(env, &tokens, status))
	{
		ft_dprintf(STDERR_FILENO, SYNTAX_ERROR_PROMPT, ")");
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (false);
	}
	context = ft_get_execution_context(ft_parse(tokens), &env);
	mem = *root;
	*root = context->root;
	free(context);
	ft_btree_clear(&mem, ft_free_leaf);
	if (!handle_subshell_simple(root, tokens, env, status))
		return (false);
	return (true);
}

static bool	verif(t_leaf *leaf)
{
	return (leaf->type == NODE_WORD && leaf->cmd && leaf->cmd->args
		&& leaf->cmd->args[0] && leaf->cmd->args[0][0]
		&& leaf->cmd->args[0][0] == '(');
}

bool	handle_subshell_simple(t_btree **root, t_list *tokens, t_list *env,
		int *status)
{
	t_leaf	*leaf;

	if (!root)
		return (false);
	leaf = (*root)->content;
	if (verif(leaf))
		if (!handle_subshell_utils(root, env, tokens, status))
			return (false);
	if ((*root)->left)
		if (!handle_subshell_simple(&(*root)->left, tokens, env, status))
			return (false);
	if ((*root)->right)
		if (!handle_subshell_simple(&(*root)->right, tokens, env, status))
			return (false);
	return (true);
}
