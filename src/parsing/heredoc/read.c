/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:05:21 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/10 19:35:20 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fuse_content(char *content, char *input)
{
	if (content && ft_strlen(content) != 0)
	{
		input = ft_strjoin_free("\n", input, SECOND);
		content = ft_strjoin_free(content, input, BOTH);
	}
	else
	{
		if (ft_strlen(input) == 0)
		{
			content = ft_strjoin_free(content, "\n", FIRST);
			free(input);
		}
		else
			content = ft_strjoin_free(content, input, BOTH);
	}
	return (content);
}

bool	ft_read_heredoc(const char *delimiter, char **content)
{
	char	*input;

	while (true)
	{
		if (handle_sigint())
		{
			free(*content);
			*content = NULL;
			return (true);
		}
		input = ft_readline(PROMPT_HEREDOC, NULL, 0);
		if (!input)
		{
			free(*content);
			return (false);
		}
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		*content = fuse_content(*content, input);
	}
	return (true);
}
