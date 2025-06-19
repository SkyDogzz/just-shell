/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_tty_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:14:03 by yandry            #+#    #+#             */
/*   Updated: 2025/06/19 03:10:01 by tstephan         ###   ########.fr       */
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

static t_context	*handle_input_backend(t_list *tokens, t_list *env,
		int status)
{
	t_context	*context;
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
	if (!context)
	{
		ft_btree_clear(&tree, ft_free_leaf);
		return (NULL);
	}
	return (context);
}

static t_context	*handle_input(char *input, t_list *env, int status)
{
	t_list		*tokens;
	t_context	*context;

	if (ft_strlen(input) == 0 || is_comment(input))
		return (NULL);
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

static int	main_process(t_list *env)
{
	char		*input;
	int			status;
	t_context	*context;

	while (true)
	{
		input = readline("");
		if (!input)
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		context = handle_input(input, env, status);
		if (!context)
		{
			free(input);
			return (0);
		}
		status = ft_exec(context, true);
		if (status == 2)
			return (0);
	}
	return (status);
}

int	non_tty_shell(t_list *env)
{
	int	ret;

	ft_set_sigaction();
	ret = main_process(env);
	return (ret);
}
