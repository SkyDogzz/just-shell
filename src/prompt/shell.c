/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/14 03:30:49 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "ft_readline.h"
#include "includes/libft.h"

static const char	*g_signal_names[] = {"SIGHUP", "SIGINT", "SIGQUIT"};

static size_t	get_base_prompt_len(const char *prompt_base)
{
	char	*trimmed_prompt;
	size_t	len;

	trimmed_prompt = ft_strtrim(prompt_base, "%s");
	len = ft_strlen(trimmed_prompt);
	free(trimmed_prompt);
	len += ft_strlen(PURPLE);
	len += ft_strlen(GREEN);
	len += ft_strlen(CYAN);
	len += ft_strlen(BOLD) * 2;
	len += ft_strlen(NC) * 3;
	return (len);
}

static void	*free_prompt_info(t_prompt_info *prompt)
{
	free(prompt->user);
	prompt->user = NULL;
	free(prompt->host);
	prompt->host = NULL;
	free(prompt->path);
	prompt->path = NULL;
	free(prompt->last_exit);
	prompt->last_exit = NULL;
	return (NULL);
}

static void	init_prompt_info(t_prompt_info *prompt_info)
{
	char	*fullpath;

	prompt_info->user = ft_strdup(getenv("USER"));
	if (!prompt_info->user)
		prompt_info->user = ft_strdup("unknown");
	prompt_info->host = ft_gethostname();
	if (!prompt_info->host)
		prompt_info->host = ft_strdup("nowhere");
	fullpath = ft_strdup(getenv("PWD"));
	if (!fullpath)
		fullpath = ft_strdup("the void");
	prompt_info->path = ft_strreplace(fullpath, getenv("HOME"), "~");
	free(fullpath);
	if (g_sig >= 1)
		prompt_info->last_exit = ft_strdup(g_signal_names[g_sig - 1]);
	else
		prompt_info->last_exit = ft_strdup("✓");
	prompt_info->prompt_len = get_base_prompt_len(DEFAULT_PROMPT)
		+ ft_strlen(prompt_info->user) + ft_strlen(prompt_info->host)
		+ ft_strlen(prompt_info->path) + ft_strlen(prompt_info->last_exit);
}

static char	*get_prompt_main(void)
{
	char			*prompt;
	t_prompt_info	prompt_info;

	init_prompt_info(&prompt_info);
	prompt = ft_calloc(prompt_info.prompt_len + 1, sizeof(char));
	if (!prompt)
		return (free_prompt_info(&prompt_info));
	ft_snprintf(prompt, prompt_info.prompt_len, DEFAULT_PROMPT,
		PURPLE, BOLD, prompt_info.user, prompt_info.host, NC,
		GREEN, BOLD, prompt_info.path, NC, prompt_info.last_exit, CYAN, NC);
	free_prompt_info(&prompt_info);
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
	if (prompt != NULL)
	{
		input = readline(prompt);
		free(prompt);
		return (input);
	}
	return (readline("ssh-xx-1.0$"));
}
