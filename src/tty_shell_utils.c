/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_shell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:41:29 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 12:42:33 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"

static bool	ft_heap_sanity_check(void)
{
	void	*test;

	test = malloc(INT_MAX >> 8);
	if (!test)
	{
		ft_dprintf(STDERR_FILENO, "the heap failed ahh run away\n");
		return (false);
	}
	free(test);
	return (true);
}

static char	*ft_get_valid_input(t_list *env, int status)
{
	char	*input;

	input = ft_readline(PROMPT_MAIN, env, status);
	if (!input)
		return (NULL);
	input = ft_handle_multiline_quote(input);
	if (!input)
		return (NULL);
	return (input);
}

static int	ft_handle_context(char *input, t_list *env, int status)
{
	t_contex2	*context;
	int			new_status;

	context = handle_input(input, env, status);
	if (!context)
		return (status);
	new_status = ft_exec(context);
	ft_free_context(context, false);
	return (new_status);
}

int	main_process_tty(t_list *env)
{
	char		*input;
	int			status;

	status = 0;
	while (true)
	{
		if (!ft_heap_sanity_check())
			return (status);
		input = ft_get_valid_input(env, status);
		if (!input)
			break ;
		status = ft_handle_context(input, env, status);
		free(input);
		if (status == 238)
			return (0);
	}
	return (status);
}
