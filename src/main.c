/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/05 15:25:38 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			g_sig = 0;

static t_tree	*cat_thing_pipe_grep_something(void)
{
	t_tree	*root;

	root = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!root)
		return (NULL);
	root->type = NODE_PIPE;
	root->left = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!root->left)
	{
		free(root);
		return (NULL);
	}
	root->left->type = NODE_WORD;
	root->right = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!root->right)
	{
		free(root->left);
		free(root->right);
		return (NULL);
	}
	root->right->type = NODE_WORD;

	root->left->cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	root->right->cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));

	root->left->cmd->args = ft_split("cat -e Makefile", ' ');
	root->right->cmd->args = ft_split("grep #", ' ');

	return (root);
}

static t_tree	*ls(void)
{
	t_tree	*root;

	root = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!root)
		return (NULL);
	root->type = NODE_WORD;
	root->cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!root->cmd)
	{
		free(root);
		return (NULL);
	}
	root->cmd->args = ft_split("lasfjnklawsrfbjklwes -lRa src/", ' ');
	return (root);
}

static int	main_process(char *argp[])
{
	//char		*input;
	//char		*prompt;
	//t_readline	ft_readline;

	return (1 ? ft_exec(cat_thing_pipe_grep_something(), argp) : ft_exec(ls(), argp));
	//ft_readline = readline;
	while (true)
	{
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			continue ;
		}
		//prompt = ft_strjoin(getenv("PWD"), " ~> ");
		//input = ft_readline(prompt);
		//free(prompt);
		//if (!input)
			//break ;
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
