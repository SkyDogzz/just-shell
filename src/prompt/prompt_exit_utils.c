/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_exit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:56:13 by yandry            #+#    #+#             */
/*   Updated: 2025/06/26 15:04:11 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"
#include "minishell.h"
#include "ft_signals.h"

const char	*get_exited_status(int status)
{
	char		*exit;
	char		*failure;
	char		*temp;
	const char	*last_status;

	exit = ft_itoa(WEXITSTATUS(status));
	failure = ft_strjoin(RED"✘ - ", exit);
	temp = ft_strdup(failure);
	free(failure);
	last_status = ft_strjoin(temp, NC);
	free(temp);
	free(exit);
	return (last_status);
}

const char	*get_signaled_status(int status, bool include_desc)
{
	const t_sig_pair	*signal;
	char				*buffer;

	signal = get_signal(WTERMSIG(status));
	if (!signal)
		return (ft_strdup(ORANGE SIGNAL_NONE NC));
	buffer = ft_calloc(sizeof(char), 64);
	if (!buffer)
		return (ft_strdup(ORANGE SIGNAL_NONE NC));
	if (include_desc)
		ft_snprintf(buffer, 64, ORANGE SIGNAL_WITH_DESC NC,
			signal->signal_name, signal->signal_description);
	else
		ft_snprintf(buffer, 64, ORANGE SIGNAL_SIMPLE NC, signal->signal_name);
	free((void *)signal);
	return (buffer);
}

const char	*get_prompt_last_exit(int last_exit, bool include_desc)
{
	const char	*last_status;

	if (last_exit & CMD_NOT_FOUND_FLAG)
		last_status = ft_strdup(RED"✘ - not found"NC);
	else if (last_exit & CANT_OPEN_OUTFILE)
		last_status = ft_strdup(RED"✘ - can't open outfile"NC);
	else if (last_exit & CANT_OPEN_INFILE)
		last_status = ft_strdup(RED"✘ - can't open infile"NC);
	else if (last_exit & SYNTAX_ERROR)
		last_status = ft_strdup(RED"✘ - syntax error"NC);
	else if (WEXITSTATUS(last_exit) == 0 && !WIFSIGNALED(last_exit))
		return (ft_strdup(GREEN"✓"NC));
	else if (WIFEXITED(last_exit))
		last_status = get_exited_status(last_exit);
	else if (WIFSIGNALED(last_exit))
		last_status = get_signaled_status(last_exit, include_desc);
	else
		last_status = ft_strdup("N/A");
	return (last_status);
}
