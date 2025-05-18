/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/17 23:15:15 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "minishell.h"
#include "ft_env.h"
#include "ft_history.h"
#include <stdlib.h>

int	g_exit = 0;

static bool	is_comment(char *input)
{
	while (ft_isspace(*input))
		input++;
	if (*input == '#')
		return (true);
	return (false);
}

static int	handle_input(char *input, t_list *env)
{
	t_list		*tokens;
	t_context	*context;
	t_btree		*tree;
	int			ret;

	ret = 0;
	if (ft_strlen(input) == 0 || is_comment(input))
		return (1);
	store_history(input, env);
	tokens = ft_lex(env, input);
	if (!tokens)
		return (0);
	if (!ft_findsubshell(env, &tokens))
	{
		printf("Syntax error near unexpected token ')'\n");
		ft_lstclear(&tokens, ft_lstclear_t_token);
		g_exit = 2;
		return (0);
	}
	tree = ft_parse(tokens);
	if (!tree)
		return (0);
	context = ft_get_execution_context(tree, env);
	if (!context)
	{
		ft_btree_clear(&tree, ft_free_leaf);
		return (0);
	}
	ret = ft_exec(context);
	ft_free_context(context);
	if (ret == 238)
		return (2);
	return (ret);
}

static int	main_process_interactive(t_list *env)
{
	char	*input;
	int		status;

	while (true)
	{
		input = ft_readline(PROMPT_MAIN, env);
		if (!input)
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		status = handle_input(input, env);
		free(input);
		if (status == 1)
			continue ;
		else if (status == 2)
			return (0);
	}
	return (0);
}

static int	main_process_non_interactive(t_list *env)
{
	char	*input;
	int		status;

	while (true)
	{
		input = readline("");
		if (!input)
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		status = handle_input(input, env);
		free(input);
		if (status == 1)
			continue ;
		else if (status == 2)
			return (0);
	}
	return (0);
}

/**
 * We are in interactive mode. Make sure to show a neat little prompt
 * and everything the user needs to not want to die while using our shell
 */
int	tty_shell(t_list *env)
{
	int	ret;

	(void)ret;
	(void)env;
	printf("interactive mode or something\n");
	retreive_history(env);
	ret = main_process_interactive(env);
	rl_clear_history();
	return (0);
}

/**
 * Non-interactive mode. We're free to run shit like we want without
 * having to worry about giving some sort of feedback to the user.
 * They better know how to write scripts.
 */
int	non_tty_shell(t_list *env)
{
	(void)env;
	printf("non-interactive mode or something\n");
	return (main_process_non_interactive(env));
}

int	main(int argc, char *argv[], char *argp[])
{
	t_list	*env;
	int		final_ret;

	env = ft_init_env((const char **)argp);
	ft_set_sigaction();
	if (isatty(STDIN_FILENO) == 1)
		final_ret = tty_shell(env);
	else
		final_ret = non_tty_shell(env);
	ft_clear_env(env);
	exit(final_ret);
	(void) argc;
	(void) argv;
}
