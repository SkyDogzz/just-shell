/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/03 21:34:08 by Yanis Andry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			g_sig = 0;

static int	main_process(char *argp[])
{
	char		*input;
	char		*prompt;
	t_readline	ft_readline;
	t_tree		*root;

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
		root = (t_tree *)malloc(sizeof(t_tree));
		root->cmd = (t_cmd *)malloc(sizeof(t_cmd));
		root->cmd->args = ft_split(input, ' ');
		ft_exec(root);
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
