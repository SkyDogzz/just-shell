/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:32:25 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 19:52:49 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"

static bool	is_comment(char *input)
{
	while (ft_isspace(*input))
		input++;
	return (*input == '#');
}

static t_list	*tokenize_and_validate(char *input, t_list *env)
{
	t_list	*tokens;

	tokens = ft_lex(env, input);
	if (!tokens)
		return (NULL);
	if (!ft_findsubshell(env, &tokens))
	{
		ft_putendl_fd("Syntax error near unexpected token ')'", STDERR_FILENO);
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (NULL);
	}
	return (tokens);
}

static t_context	*build_context(t_btree *tree, t_list *tokens,
					t_list *env, int fd[2])
{
	t_context	*context;

	context = ft_get_execution_context(tree, env);
	if (!context)
		return (NULL);
	context->fdin = fd[0];
	context->fdout = fd[1];
	if (!handle_subshell_simple(&context->root, tokens, env))
	{
		ft_btree_clear(&context->root, ft_free_leaf);
		free(context);
		return (NULL);
	}
	return (context);
}

t_context	*handle_input(char *input, t_list *env, int fd[2])
{
	t_list		*tokens;
	t_context	*context;
	t_btree		*tree;

	if (ft_strlen(input) == 0 || is_comment(input))
		return (NULL);
	tokens = tokenize_and_validate(input, env);
	if (!tokens)
		return (NULL);
	tree = ft_parse(tokens);
	if (!tree)
		return (NULL);
	context = build_context(tree, tokens, env, fd);
	if (!context)
	{
		ft_btree_clear(&tree, ft_free_leaf);
		return (0);
	}
	return (context);
}
