/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:26:10 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/18 16:08:06 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*ft_quit_subshell(char *content)
{
	free(content);
	return (NULL);
}

static int	get_level(int level, char *input)
{
	while (*input)
	{
		if (*input == ')')
			level--;
		if (*(input + 1) && (*input == '$' && *(input + 1) == '('))
		{
			level++;
		}
		input++;
	}
	return (level);
}

static char	*fuse_content(char *content, const char *input)
{
	if (content && ft_strlen(content) != 0)
	{
		input = ft_strjoin_free("\n", input, NONE);
		content = ft_strjoin_free(content, input, BOTH);
	}
	else
	{
		if (ft_strlen(input) == 0)
			content = ft_strjoin_free(content, "\n", FIRST);
		else
			content = ft_strjoin_free(content, input, FIRST);
	}
	return (content);
}

char	*ft_read_subshell(int level)
{
	char	*content;
	char	*input;

	content = ft_strdup("");
	while (true)
	{
		if (handle_sigint())
			return (ft_quit_subshell(content));
		input = ft_readline(PROMPT_SUBSHELL);
		if (!input)
			return (ft_quit_subshell(content));
		level = get_level(level, input);
		if (level == 0)
		{
			content = fuse_content(content, input);
			free(input);
			break ;
		}
		content = fuse_content(content, input);
		free(input);
	}
	printf("content %s\n", content);
	return (content);
}
