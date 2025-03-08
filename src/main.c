/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/01 19:13:08 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	g_sig = 0;

static int	handle_input(char *input)
{
	t_list	*tokens;
	t_tree	*root;

	if (ft_strlen(input) == 0)
	{
		free(input);
		return (0);
	}
	add_history(input);
	tokens = ft_lex(input);
	root = ft_parse(tokens);
	ft_lstclear(&tokens, free);
	ft_print_tree(root, 0, 1);
	//ft_exec(root);
	free(input);
	return (1);
}

static int	main_process(char *argp[])
{
	char		*input;
	char		*prompt;
	t_readline	ft_readline;

	ft_readline = readline;
	while (true)
	{
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			continue ;
		}
		prompt = ft_strjoin(getenv("PWD"), " ~> ");
		input = ft_readline(prompt);
		free(prompt);
		if (!input)
			break ;
		if (!handle_input(input))
			continue ;
	}
	return (0);
	(void)argp;
}

int	main(int argc, char *argv[], char *argp[])
{
	int	exit_code;

	ft_set_sigaction();
	exit_code = main_process(argp);
	printf("exit\n");
	return (exit_code);
	(void)argc;
	(void)argv;
}
