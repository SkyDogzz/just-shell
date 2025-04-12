/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/12 23:33:06 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "ft_readline.h"

static const char	*g_signal_names[] = {"SIGHUP", "SIGINT", "SIGQUIT"};

static char	*prompt_with_user_at_host(const char	*old_prompt)
{
	char	*with_user;
	char	*with_host;
	char	*user;
	char	*host;

	user = getenv("USER");
	if (!user)
		user = "unknown";
	host = ft_gethostname();
	if (!host)
		host = ft_strdup("nowhere");
	with_user = ft_strreplace(old_prompt, "$user", user);
	with_host = ft_strreplace(with_user, "$host", host);
	free(with_user);
	free(host);
	return (with_host);
}

static char	*prompt_with_path_and_exit(const char	*old_prompt)
{
	char	*with_path;
	char	*with_exit;
	char	*path;
	char	*temp_path;
	char	*last_exit;

	temp_path = ft_strdup(getenv("PWD"));
	if (!temp_path)
		temp_path = ft_strdup("the void");
	path = ft_strreplace(temp_path, getenv("HOME"), "~");
	if (g_sig >= 1)
		last_exit = ft_strdup(g_signal_names[g_sig - 1]);
	else
		last_exit = ft_strdup("✓");
	with_path = ft_strreplace(old_prompt, "$path", path);
	with_exit = ft_strreplace(with_path, "$last_exit", last_exit);
	free(with_path);
	free(last_exit);
	free(temp_path);
	free(path);
	return (with_exit);
}

static char	*get_prompt_main(void)
{
	char	*prompt;
	char	*temp;

	temp = prompt_with_user_at_host(DEFAULT_PROMPT);
	prompt = prompt_with_path_and_exit(temp);
	free(temp);
	return (prompt);
}

char	*ft_readline(t_prompt id)
{
	char	*prompt;
	char	*input;

	if (id == PROMPT_HEREDOC)
		return (readline(CYAN BOLD "heredoc> " NC));
	else if (id == PROMPT_QUOTE)
		return (readline(CYAN BOLD "quote> " NC));
	else if (id == PROMPT_SUBSHELL)
		return (readline(CYAN BOLD "subshell> " NC));
	else
		prompt = get_prompt_main();
	input = readline(prompt);
	free(prompt);
	return (input);
}
