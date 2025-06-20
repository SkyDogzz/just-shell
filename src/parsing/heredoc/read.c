/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:05:21 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/27 16:30:38 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_quit_heredoc(char *content)
{
	free(content);
	return (NULL);
}

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

char	*ft_read_heredoc(const char *delimiter)
{
	char	*content;
	char	*input;

	content = ft_strdup("");
	while (true)
	{
		if (handle_sigint())
			return (ft_quit_heredoc(content));
		input = ft_readline(PROMPT_HEREDOC, NULL, 0);
		if (!input)
			return (ft_quit_heredoc(content));
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		content = fuse_content(content, input);
	}
	return (content);
}
