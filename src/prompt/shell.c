/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/15 15:32:35 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "includes/libft.h"

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
