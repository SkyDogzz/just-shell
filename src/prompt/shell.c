/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/12 16:36:32 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_prompt_main(void)
{
	char	*prompt;
	char	*mem;
	
	prompt = ft_strjoin(GREEN BOLD "Maxishell | ", ft_getenv("PWD"));
	mem = ft_strjoin(prompt, " > " NC);
	free(prompt);
	prompt = ft_strreplace(mem, ft_getenv("HOME"), "~");
	free(mem);
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
