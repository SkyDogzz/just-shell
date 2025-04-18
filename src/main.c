/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/17 18:01:29 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

int	g_exit;

static bool	is_comment(char *input)
{
	while (ft_isspace(*input))
		input++;
	if (*input == '#')
		return (true);
	return (false);
}

static bool	is_exit(char *input)
{
	return (ft_strlen(input) == 4 && ft_strcmp(input, "exit") == 0);
}

static int	handle_input(char *input, t_list *env)
{
	t_list	*tokens;
	t_btree	*tree;

	if (ft_strlen(input) <= 0 || is_comment(input))
		return (1);
	if (is_exit(input))
		return (2);
	add_history(input);
	tokens = ft_lex(input);
	if (!tokens)
		return (0);
	if (!ft_findsubshell(&tokens))
	{
		printf("Syntax error near unexpected token ')'\n");
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (0);
	}
	tree = ft_parse(tokens);
	ft_exec(tree, env);
	ft_btree_clear(&tree, ft_free_leaf);
	return (0);
}

static int	main_process(t_list *env)
{
	char	*input;
	int		status;

	while (true)
	{
		input = ft_readline(PROMPT_MAIN);
		if (!input)
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		status = handle_input(input, env);
		if (status == 1)
		{
			free(input);
			continue ;
		}
		else if (status == 2)
			return (free(input), 0);
		free(input);
	}
	return (0);
}

int	main(int argc, char *argv[], char *argp[])
{
	int		exit_code;
	t_list	*env;

	env = ft_init_env((const char **)argp);
	ft_set_sigaction();
	g_exit = 0;
	exit_code = main_process(env);
	rl_clear_history();
	ft_lstclear(&env, clear_env);
	return (exit_code);
	(void) argc;
	(void) argv;
	(void) argp;
}
