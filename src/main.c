/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/14 14:44:14 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

static bool	is_exit(char *input)
{
	if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
	{
		free(input);
		return (true);
	}
	return (false);
}

static int	main_process(void)
{
	t_list	*tokens;
	t_btree	*tree;
	char	*input;

	while (true)
	{
		if (handle_sigint())
			continue ;
		input = ft_readline(PROMPT_MAIN);
		if (!input)
			break ;
		if (is_exit(input))
			return (0);
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		if (ft_strlen(input) <= 0)
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
				continue ;
			}
			tree = ft_parse(tokens);
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
	exit_code = main_process();
	printf("exit\n");
	return (exit_code);
	(void) argc;
	(void) argv;
	(void) argp;
}
