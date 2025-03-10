/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/10 14:40:58 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

static bool	ft_quote_ended(const char *input)
{
	t_quote	quote;

	quote = UQUOTE;
	while (*input)
	{
		if (quote == UQUOTE)
		{
			if (ft_isin_charset(*input, QUOTE))
			{
				quote = SQUOTE;
				if (*input == '"')
					quote = DQUOTE;
			}
		}
		else if (quote == DQUOTE)
		{
			if (*input == '"' && *(input - 1) != '\\')
				quote = UQUOTE;
		}
		else
			if (*input == '\'')
				quote = UQUOTE;
		input++;
	}
	if (quote == UQUOTE)
		return (true);
	return (false);
}

static char	*ft_handle_multiline_quote(char *input)
{
	char	*mem;
	char	*rest;

	while (!ft_quote_ended(input))
	{
		if (handle_sigint())
		{
			free(input);
			return (NULL);
		}
		mem = ft_strjoin(input, "\n");
		free(input);
		rest = readline("> ");
		if (!rest)
		{
			free(mem);
			return (NULL);
		}
		input = ft_strjoin(mem, rest);
		free(mem);
		free(rest);
	}
	return (input);
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
		input = readline("Minishell : ");
		if (!input)
			break ;
		if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			return (0);
		}
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		add_history(input);
		tokens = ft_lex(input);
		if (tokens)
		{
			ft_lstprint_tokens(tokens, "Print strings :");
			tree = ft_parse(tokens);
			ft_lstclear(&tokens, ft_lstclear_t_token);
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
