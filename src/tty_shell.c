/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:46:49 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 09:57:24 by tstephan         ###   ########.fr       */
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

static t_context	*handle_input(char *input, t_list *env, int fd[2])
{
	t_list		*tokens;
	t_context	*context;
	t_btree		*tree;

	if (ft_strlen(input) == 0 || is_comment(input))
		return (NULL);
	store_history(input, env);
	tokens = ft_lex(env, input);
	if (!tokens)
		return (NULL);
	input = NULL;
	if (!ft_findsubshell(env, &tokens))
	{
		ft_putendl_fd("Syntax error near unexpected token ')'", STDERR_FILENO);
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (NULL);
	}
	tree = ft_parse(tokens);
	if (!tree)
		return (NULL);
	context = ft_get_execution_context(tree, env);
	context->fdin = fd[0];
	context->fdout = fd[1];
	if (!handle_subshell_simple(&context->root, tokens, env))
	{
		ft_btree_clear(&context->root, ft_free_leaf);
		free(context);
		return (0);
	}
	if (!context)
	{
		ft_btree_clear(&tree, ft_free_leaf);
		return (0);
	}
	return (context);
}

static int	main_process_tty(t_list *env)
{
	char		*input;
	int			status;
	t_context	*context;
	int		fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	status = 0;
	while (true)
	{
		input = ft_readline(PROMPT_MAIN, env, status);
		if (!input)
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		context = handle_input(input, env, fd);
		if (!context)
		{
			free(input);
			continue ;
		}
		status = ft_exec(context);
		ft_free_context(context, false);
		if (status == 238)
			return (0);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	return (status);
}

int	tty_shell(t_list *env)
{
	int	ret;

	ft_set_sigaction();
	retreive_history(env);
	ret = main_process_tty(env);
	rl_clear_history();
	return (ret);
}
