/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/01 16:23:34 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_prompt.h"
#include "includes/libft.h"

static char	*extract_from_stash(char **stash)
{
	char	*nl;
	char	*line;
	char	*rest;

	if (!*stash)
		return (NULL);
	nl = strchr(*stash, '\n');
	if (!nl)
		return (NULL);
	*nl = '\0';
	line = strdup(*stash);
	rest = strdup(nl + 1);
	free(*stash);
	*stash = rest;
	return (line);
}

static int	append_to_stash(char **stash, char *buf)
{
	size_t	old;
	size_t	new;
	char	*joined;

	if (!buf)
		return (0);
	if (*stash)
		old = strlen(*stash);
	else
		old = 0;
	new = old + strlen(buf) + 2;
	joined = malloc(new);
	if (!joined)
		return (free(buf), 0);
	if (*stash)
		strcpy(joined, *stash);
	else
		joined[0] = '\0';
	strcat(joined, buf);
	strcat(joined, "\n");
	free(*stash);
	free(buf);
	*stash = joined;
	return (1);
}

static char	*read_once(char **stash, const char *prompt)
{
	char	*buf;

	buf = readline(prompt);
	if (!buf)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	if (!append_to_stash(stash, buf))
		return (NULL);
	return (extract_from_stash(stash));
}

static char	*ft_readline_in(const char *prompt)
{
	static char	*stash;
	char		*line;

	line = extract_from_stash(&stash);
	if (line)
		return (line);
	while (1)
	{
		line = read_once(&stash, prompt);
		if (line)
			return (line);
		if (!stash)
			return (NULL);
	}
}

char	*ft_readline(t_prompt id, t_list *env)
{
	const char	*prompt;
	char		*input;

	if (id == PROMPT_HEREDOC)
		return (ft_readline_in(CYAN BOLD "heredoc> " NC));
	else if (id == PROMPT_QUOTE)
		return (ft_readline_in(CYAN BOLD "quote> " NC));
	else if (id == PROMPT_SUBSHELL)
		return (ft_readline_in(CYAN BOLD "subshell> " NC));
	else
		prompt = get_prompt_main(env);
	if (prompt != NULL)
	{
		input = ft_readline_in(prompt);
		free((void *)prompt);
		return (input);
	}
	return (ft_readline_in("ssh-xx-1.0$"));
}
