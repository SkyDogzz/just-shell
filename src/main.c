/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 20:11:57 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

static int	main_process(void)
{
	t_list	*tokens;
	t_tree	*tree;
	char	*input;

	while (true)
	{
		if (handle_sigint())
			continue ;
		input = readline("Minishell : ");
		if (!input)
			break ;
		if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			return (0);
		}
		add_history(input);
		tokens = ft_lex(input);
		if (tokens)
		{
			ft_lstprint_tokens(tokens, "Print strings :");
			tree = ft_parse(tokens);
			ft_lstclear(&tokens, ft_lstclear_t_token);
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
