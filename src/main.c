/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/17 18:41:51 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

int	main_process(char *argp[])
{
	t_token	*tokens;
	char	*input;

	while (TRUE)
	{
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			continue ;
		}
		input = readline("Minishell : ");
		if (!input)
			break;
		tokens = parse_tokens(input);
		token_free(tokens);
		free(input);
	}
	return (0);
	(void) argp;
}

int	main(int argc, char *argv[], char *argp[])
{
	int	exit_code;

	set_signal_action();
	exit_code = main_process(argp);
	printf("exit\n");
	return (EXIT_SUCCESS);
	(void) argc;
	(void) argv;
}
