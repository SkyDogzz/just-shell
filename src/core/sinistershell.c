/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinistershell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:19:19 by yandry            #+#    #+#             */
/*   Updated: 2025/04/18 17:46:16 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean(char *input, t_list *env)
{
	if (input)
		free(input);
	if (env)
		ft_lstclear(&env, clear_env);
}

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
	return (ft_strlen(input) == 4 && ft_strcmp(input, "exit") == 0);
}

static int	handle_input(char *input, t_list *env)
{
	t_list	*tokens;
	t_btree	*tree;

	if (ft_strlen(input) <= 0 || is_comment(input))
		return (1);
	if (is_exit(input))
		return (2);
	add_history(input);
	tokens = ft_lex(input);
	if (!tokens)
		return (0);
	if (!ft_findsubshell(&tokens))
	{
		printf("Syntax error near unexpected token ')'\n");
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (0);
	}
	tree = ft_parse(tokens);
	ft_exec(tree, env);
	ft_btree_clear(&tree, ft_free_leaf);
	return (0);
}

int	ft_sinistre(char **env)
{
	char	*input;
	int		status;
	t_list	*env_list;

	env_list = ft_init_env((const char **)env);
	while (true)
	{
		input = ft_readline(PROMPT_MAIN);
		if (!input)
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		status = handle_input(input, env_list);
		if (status == 1)
		{
			clean(input, env_list);
			continue ;
		}
		else if (status == 2)
			return (clean(input, env_list), 0);
		free(input);
	}
	ft_lstclear(&env_list, clear_env);
	return (0);
}
