/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/20 22:28:52 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_prompt.h"
#include "includes/libft.h"

char	*ft_readline(t_prompt id, t_list *env)
{
	const char	*prompt;
	char		*input;

	if (id == PROMPT_HEREDOC)
		return (readline(CYAN BOLD "heredoc> " NC));
	else if (id == PROMPT_QUOTE)
		return (readline(CYAN BOLD "quote> " NC));
	else if (id == PROMPT_SUBSHELL)
		return (readline(CYAN BOLD "subshell> " NC));
	else
		prompt = get_prompt_main(env);
	if (prompt != NULL)
	{
		input = readline(prompt);
		free((void *)prompt);
		return (input);
	}
	return (readline("ssh-xx-1.0$"));
}
