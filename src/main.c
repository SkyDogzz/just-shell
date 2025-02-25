/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/25 18:46:05 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

int	main_process(char *argp[])
{
	t_list	*tokens;
	char	*input;

	while (true)
	{
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			continue ;
		}
		input = readline("Minishell : ");
		if (!input)
			break ;
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = ft_lex(input);
		ft_lstclear(&tokens, ft_lstclear_string);
		free(input);
	}
	return (0);
	(void) argp;
}

int	main(int argc, char *argv[], char *argp[])
{
	int	exit_code;

	ft_set_sigaction();
	exit_code = main_process(argp);
	printf("exit\n");
	return (exit_code);
	(void) argc;
	(void) argv;
}
