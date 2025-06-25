/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:46:49 by yandry            #+#    #+#             */
/*   Updated: 2025/06/26 00:48:02 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_history.h"
#include "minishell.h"

static bool	is_comment(char *input)
{
	while (ft_isspace(*input))
		input++;
	return (*input == '#');
}

static t_contex2	*handle_input_backend(t_list *tokens, t_list *env,
		int status)
{
	t_contex2	*context;
	t_btree		*tree;

	tree = ft_parse(tokens);
	if (!tree)
		return (NULL);
	context = ft_get_execution_context(tree, env);
	if (!handle_subshell_simple(&context->root, tokens, env, status))
	{
		ft_btree_clear(&context->root, ft_free_leaf);
		free(context);
		return (NULL);
	}
	context->context = context->root;
	if (!context)
	{
		ft_btree_clear(&tree, ft_free_leaf);
		return (NULL);
	}
	return (context);
}

t_contex2	*handle_input(char *input, t_list *env, int status)
{
	t_list		*tokens;
	t_contex2	*context;

	if (ft_strlen(input) == 0 || is_comment(input))
		return (NULL);
	store_history(input, env);
	tokens = ft_lex(env, input, status);
	if (!tokens)
		return (NULL);
	input = NULL;
	if (!ft_findsubshell(env, &tokens, status))
	{
		ft_putendl_fd("Syntax error near unexpected token ')'", STDERR_FILENO);
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (NULL);
	}
	context = handle_input_backend(tokens, env, status);
	return (context);
}

int	tty_shell(t_list *env)
{
	int	ret;

	retreive_history(env);
	ret = main_process_tty(env);
	rl_clear_history();
	return (ret);
}
