/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/05 16:47:39 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_prompt_main(void)
{
	char	*prompt;
	char	*mem;

	prompt = ft_strjoin_free(GREEN BOLD "Maxishell | ", ft_getenv("PWD"), NONE);
	prompt = ft_strjoin_free(prompt, " > " NC, FIRST);
	mem = ft_strreplace(prompt, ft_getenv("HOME"), "~");
	free(prompt);
	return (mem);
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
	//input = readline(prompt);
	input = ft_strdup("cat Makefile | grep # | wc -l");
	free(prompt);
	return (input);
}
