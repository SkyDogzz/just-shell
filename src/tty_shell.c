/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:46:49 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 19:40:14 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_history.h"
#include "minishell.h"

t_context	*handle_input(char *input, t_list *env, int fd[2]);

static void	manage_tty_fds(int fd[2], bool restore)
{
	if (!restore)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
}

static char	*process_input(t_list *env, int status)
{
	char	*input;

	input = ft_readline(PROMPT_MAIN, env, status);
	if (!input)
		return (NULL);
	input = ft_handle_multiline_quote(input);
	return (input);
}

static int	process_command(char *input, t_list *env, int fd[2])
{
	t_context	*context;
	int			status;

	store_history(input, env);
	context = handle_input(input, env, fd);
	if (!context)
		return (-1);
	status = ft_exec(context);
	ft_free_context(context, false);
	return (status);
}

static int	main_process_tty(t_list *env)
{
	char		*input;
	int			status;
	int			fd[2];

	manage_tty_fds(fd, false);
	status = 0;
	while (true)
	{
		input = process_input(env, status);
		if (!input)
			break ;
		if (!*input)
			continue ;
		status = process_command(input, env, fd);
		free(input);
		if (status == -1)
			continue ;
		if (status == 238)
			return (0);
		manage_tty_fds(fd, true);
	}
	return (status);
}

int	tty_shell(t_list *env)
{
	int	ret;

	ft_set_sigaction();
	retreive_history(env);
	ret = main_process_tty(env);
	rl_clear_history();
	return (ret);
}
