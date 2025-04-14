/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/14 15:26:31 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

int	g_sig;

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
	if (ft_strlen(input) == 4 && ft_strcmp(input, "exit") == 0)
	{
		free(input);
		return (true);
	}
	return (false);
}

static int	main_process(char **env)
{
	t_list	*tokens;
	t_btree	*tree;
	char	*input;

	tokens = NULL;
	tree = NULL;
	while (true)
	{
		input = ft_readline(PROMPT_MAIN);
		if (!input)
			break ;
		if (is_exit(input))
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		if (ft_strlen(input) <= 0 || is_comment(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = ft_lex(input);
		if (tokens)
		{
			if (!ft_findsubshell(&tokens))
			{
				printf("Syntax error near unexpected token ')'\n");
				ft_lstclear(&tokens, ft_lstclear_t_token);
				free(input);
				continue ;
			}
			tree = ft_parse(tokens);
			ft_exec(tree, env);
			ft_btree_clear(&tree, ft_free_leaf);
		}
		free(input);
	}
	return (0);
}

int	main(int argc, char *argv[], char *argp[])
{
	int		exit_code;

	ft_set_sigaction();
	g_sig = 0;
	exit_code = main_process(argp);
	rl_clear_history();
	return (exit_code);
	(void) argc;
	(void) argv;
	(void) argp;
}
