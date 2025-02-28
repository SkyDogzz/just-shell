/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/28 19:35:58 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig = 0;

t_list	*ft_lex(const char *input)
{
	t_token	*tok;
	t_list	*node;
	t_list	*list;
	char	**split;

	list = NULL;
	split = ft_split(input, ' ');
	if (!split)
		return (NULL);
	while (*split)
	{
		tok = ft_new_token(*split++);
		if (!tok)
			return (ft_lstclear(&list, free), NULL);
		node = ft_lstnew(tok);
		if (!node)
			return (ft_lstclear(&list, free), NULL);
		ft_lstadd_back(&list, node);
	}
	return (list);
}

t_tree	*ft_parse(t_list *tokens)
{
	t_tree	*root;

	root = (t_tree *)malloc(sizeof(t_tree));
	if (!root)
		return (NULL);
	while (tokens)
	{
		if (((t_token *)tokens->content)->token_type == T_OPERATOR)
		{
			if (ft_strncmp(((t_token *)tokens->content)->content, "|", 1) == 0)
				root->right = ft_parse(tokens->next);
		}
		tokens = tokens->next;
	}
	return (root);
}

int	main_process(char *argp[])
{
	t_list		*tokens;
	t_tree		*root;
	char		*input;
	t_readline	ft_readline;

	ft_readline = readline;
	while (true)
	{
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			continue ;
		}
		input = ft_readline("ssh-xx ~>");
		if (!input)
			break ;
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = ft_lex(input);
		root = ft_parse(tokens);
		ft_exec(root);
		free(input);
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
