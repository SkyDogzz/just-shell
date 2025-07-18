/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_shell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:41:29 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/11 15:44:55 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_history.h"

static char	*ft_get_valid_input(t_list *env, int *status)
{
	char	*input;
	char	*mem;

	input = ft_readline(PROMPT_MAIN, env, *status);
	if (!input)
		return (NULL);
	if (ft_strcmp(input, "") == 0)
	{
		if (handle_sigint())
			*status = SIGINT;
		return (input);
	}
	input = ft_handle_multiline_quote(input);
	if (!input)
	{
		*status = SIGINT;
		input = ft_strdup("");
	}
	mem = input;
	input = ft_strtrim(mem, " \t\n\r\v");
	free(mem);
	return (input);
}

static int	exit_code_extractor(int status)
{
	int	exit_code;

	if (status & EXIT_SHELL)
		exit_code = status & 0xFF;
	else if (status & CMD_NOT_FOUND_FLAG)
		exit_code = 127;
	else if (status & (CANT_OPEN_INFILE | CANT_OPEN_OUTFILE))
		exit_code = 1;
	else
	{
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		else
			exit_code = status & 0xFF;
	}
	return (exit_code);
}

static int	ft_handle_context(char *input, t_list **env, int status)
{
	t_context	*context;
	int			new_status;
	char		*status_str;

	context = handle_input(input, env, &status);
	free(input);
	if (!context)
		return (status);
	ft_set_sigaction_no_inter();
	new_status = ft_exec(context, true);
	*env = context->env;
	ft_set_sigaction();
	ft_free_context(context, false);
	status_str = ft_itoa(exit_code_extractor(new_status));
	if (status_str)
	{
		ft_update_env(env, "?", status_str, false);
		free(status_str);
	}
	return (new_status);
}

int	main_process_tty(t_list **env)
{
	char		*input;
	int			status;

	status = 0;
	while (true)
	{
		handle_sigint();
		input = ft_get_valid_input(*env, &status);
		if (!input)
			break ;
		store_history(input, *env);
		status = ft_handle_context(input, env, status);
		if (status & EXIT_SHELL)
			return (status & 0xFF);
	}
	return (status);
}
