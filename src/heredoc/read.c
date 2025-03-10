/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:05:21 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/10 15:25:40 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*ft_quit_heredoc(char *content)
{
	free(content);
	return (NULL);
}

static char	*fuse_content(char *content, char *input)
{
	char	*mem;
	char	*inputendl;

	mem = content;
	if (ft_strlen(mem) != 0)
	{
		inputendl = ft_strjoin("\n", input);
		content = ft_strjoin(mem, inputendl);
		free(mem);
		free(inputendl);
	}
	else
	{
		if (ft_strlen(input) == 0)
			content = ft_strjoin(mem, "\n");
		else
			content = ft_strjoin(mem, input);
		free(mem);
	}
	return (content);
}

char	*ft_read_heredoc(char *delimiter)
{
	char	*content;
	char	*input;

	content = ft_strdup("");
	while (true)
	{
		if (handle_sigint())
			return (ft_quit_heredoc(content));
		input = readline("heredoc> ");
		if (!input)
			return (ft_quit_heredoc(content));
		if (ft_strncmp(input, delimiter, ft_getmax(ft_strlen(input),
					ft_strlen(delimiter))) == 0)
		{
			free(input);
			break ;
		}
		content = fuse_content(content, input);
		free(input);
	}
	return (content);
}
