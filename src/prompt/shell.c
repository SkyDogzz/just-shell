/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/11 15:00:45 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

static char	*ft_get_host_name(void)
{
	int		hostname_file;
	int		i;
	char	*line;
	char	**hostname;

	hostname_file = open("/etc/hostname", O_RDONLY);
	if (hostname_file == -1)
		return (NULL);
	line = ft_get_next_line(hostname_file);
	close(hostname_file);
	hostname = ft_split(line, '.');
	free(line);
	line = NULL;
	if (!hostname || !hostname[0])
		return (NULL);
	line = ft_strdup(hostname[0]);
	i = 0;
	while (hostname[i])
		free(hostname[i++]);
	free(hostname);
	return (line);
}

static char	*get_prompt_main(void)
{
	char	*prompt;
	char	*mem;
	char	*hostname;

	hostname = ft_get_host_name();
	prompt = ft_calloc(150, sizeof(char));
	sprintf(prompt, "%s%s%s @ %s%s in %s%s%s%s [last_exit_signal_yada_yada] %s>%s ", PURPLE, BOLD, getenv("USER"), hostname, NC, GREEN, BOLD, getenv("PWD"), NC, CYAN, NC);
	mem = ft_strreplace(prompt, ft_getenv("HOME"), "~");
	free(prompt);
	free(hostname);
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
	input = readline(prompt);
	//input = ft_strdup("cat Makefile | grep # | wc -l");
	free(prompt);
	return (input);
}
