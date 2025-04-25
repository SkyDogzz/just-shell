/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:51:19 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parse.h"
#include "ft_lex.h"
#include "ft_lst_helper.h"
#include "ft_utils.h"
#include "ft_prompt.h"
#include "ft_signals.h"

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
	t_list	*tokens;
	t_btree	*tree;
	int		ret;

	if (ft_strlen(input) == 0 || is_comment(input))
		return (1);
	add_history(input);
	tokens = ft_lex(env, input);
	if (!tokens)
		return (0);
	if (!ft_findsubshell(env, &tokens))
	{
		printf("Syntax error near unexpected token ')'\n");
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (0);
	}
	tree = ft_parse(tokens);
	ret = ft_exec(tree, env);
	ft_btree_clear(&tree, ft_free_leaf);
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
	main_process(env);
	rl_clear_history();
	ft_clear_env(env);
	final_ret = WEXITSTATUS(g_exit);
	exit(final_ret);
	(void) argc;
	(void) argv;
}
