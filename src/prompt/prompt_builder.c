/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:38:05 by yandry            #+#    #+#             */
/*   Updated: 2025/04/18 11:34:50 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_signals.h"

char	*get_current_wd(void);

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
	free((void *)prompt->user);
	prompt->user = NULL;
	free((void *)prompt->host);
	prompt->host = NULL;
	free((void *)prompt->path);
	prompt->path = NULL;
	free((void *)prompt->last_exit);
	prompt->last_exit = NULL;
	return (NULL);
}

static const char	*retrieve_last_exit(void)
{
	const char	*last_status;

	if (WIFEXITED(g_exit))
		last_status = get_exited_status();
	else if (WIFSIGNALED(g_exit))
		last_status = get_signaled_status();
	else
		last_status = ft_strdup("N/A");
	return (last_status);
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
	fullpath = get_current_wd();
	prompt_info->path = ft_strreplace(fullpath, getenv("HOME"), "~");
	if (!prompt_info->path)
		prompt_info->path = ft_strdup("the void *dun dun dun*");
	free(fullpath);
	prompt_info->last_exit = retrieve_last_exit();
	if (!prompt_info->last_exit)
		prompt_info->last_exit = ft_strdup("N/A");
	prompt_info->prompt_len = get_base_prompt_len(DEFAULT_PROMPT)
		+ ft_strlen(prompt_info->user) + ft_strlen(prompt_info->host)
		+ ft_strlen(prompt_info->path) + ft_strlen(prompt_info->last_exit);
}

char	*get_prompt_main(void)
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
