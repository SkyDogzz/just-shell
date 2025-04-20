/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:38:05 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 22:28:32 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"
#include "minishell.h"

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

static void	init_prompt_info(t_prompt_info *prompt_info, t_list *env)
{
	prompt_info->user = get_prompt_user(env);
	prompt_info->host = get_prompt_host(env);
	prompt_info->path = get_prompt_path(env);
	prompt_info->last_exit = get_prompt_last_exit();
	if (!prompt_info->last_exit)
		prompt_info->last_exit = ft_strdup("N/A");
	prompt_info->prompt_len = get_base_prompt_len(DEFAULT_PROMPT)
		+ ft_strlen(prompt_info->user) + ft_strlen(prompt_info->host)
		+ ft_strlen(prompt_info->path) + ft_strlen(prompt_info->last_exit);
}

const char	*get_prompt_main(t_list *env)
{
	char			*prompt;
	t_prompt_info	prompt_info;

	init_prompt_info(&prompt_info, env);
	prompt = ft_calloc(prompt_info.prompt_len + 1, sizeof(char));
	if (!prompt)
		return (free_prompt_info(&prompt_info));
	ft_snprintf(prompt, prompt_info.prompt_len, DEFAULT_PROMPT,
		PURPLE, BOLD, prompt_info.user, prompt_info.host, NC,
		GREEN, BOLD, prompt_info.path, NC, prompt_info.last_exit, CYAN, NC);
	free_prompt_info(&prompt_info);
	return (prompt);
}
