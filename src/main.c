/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/29 16:43:58 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "minishell.h"
#include "ft_env.h"
#include "ft_history.h"
#include <stdlib.h>

int	g_exit;

static bool	is_comment(char *input)
{
	while (ft_isspace(*input))
		input++;
	if (*input == '#')
		return (true);
	return (false);
}

static int	handle_input(char *input, t_list *env)
{
	t_list		*tokens;
	t_context	*context;
	int			ret;

	if (ft_strlen(input) == 0 || is_comment(input))
		return (1);
	store_history(input, env);
	tokens = ft_lex(env, input);
	if (!tokens)
		return (0);
	if (!ft_findsubshell(env, &tokens))
	{
		printf("Syntax error near unexpected token ')'\n");
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (0);
	}
	context = ft_get_execution_context(ft_parse(tokens), env);
	ret = ft_exec(context);
	ft_btree_clear(&context->root, ft_free_leaf);
	free(context);
	if (ret == 238)
		return (2);
	g_exit = ret;
	return (0);
}

static int	main_process(t_list *env)
{
	char	*input;
	int		status;

	while (true)
	{
		input = ft_readline(PROMPT_MAIN, env);
		if (!input)
			break ;
		input = ft_handle_multiline_quote(input);
		if (!input)
			continue ;
		status = handle_input(input, env);
		free(input);
		if (status == 1)
		{
			g_exit = 0;
			continue ;
		}
		else if (status == 2)
			return (0);
	}
	return (0);
}

int	main(int argc, char *argv[], char *argp[])
{
	t_list	*env;
	int		final_ret;

	env = ft_init_env((const char **)argp);
	ft_set_sigaction();
	g_exit = 0;
	retreive_history(env);
	main_process(env);
	rl_clear_history();
	ft_clear_env(env);
	final_ret = WEXITSTATUS(g_exit);
	exit(final_ret);
	(void) argc;
	(void) argv;
}
