/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_exit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:56:13 by yandry            #+#    #+#             */
/*   Updated: 2025/06/20 22:26:35 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_signals.h"

const char	*get_signal_name(int sig_no)
{
	const t_signal	*sig = g_signals;
	static char		rt_buffer[16];

	if (sig_no >= SIGRTMIN && sig_no <= SIGRTMAX)
	{
		ft_snprintf(rt_buffer, sizeof(rt_buffer),
			"SIGRT_%d", sig_no - SIGRTMIN);
		return (rt_buffer);
	}
	while (sig->sig_name)
	{
		if (sig->sig_no == sig_no)
			return (sig->sig_name);
		sig++;
	}
	return ("N/A");
}

const char	*get_exited_status(int status)
{
	char		*exit;
	char		*failure;
	char		*temp;
	const char	*last_status;

	exit = ft_itoa(WEXITSTATUS(status));
	failure = ft_strjoin(RED"✗ - ", exit);
	temp = ft_strdup(failure);
	free(failure);
	last_status = ft_strjoin(temp, NC);
	free(temp);
	free(exit);
	return (last_status);
}

const char	*get_signaled_status(int status)
{
	char		*exit;
	char		*temp;
	char		*failure;
	const char	*last_status;

	exit = ft_strdup(get_signal_name(WTERMSIG(status)));
	failure = ft_strjoin(ORANGE"🗲 - ", exit);
	temp = ft_strdup(failure);
	free(failure);
	free(exit);
	last_status = ft_strjoin(temp, NC);
	free(temp);
	return (last_status);
}

const char	*get_prompt_last_exit(int last_exit)
{
	const char	*last_status;

	if (WEXITSTATUS(last_exit << 8) == 0)
		return (ft_strdup(GREEN"✓"NC));
	else if (WIFEXITED(last_exit))
		last_status = get_exited_status(last_exit);
	else if (WIFSIGNALED(last_exit))
		last_status = get_signaled_status(last_exit);
	else if (last_exit & CMD_NOT_FOUND_FLAG)
		last_status = ft_strdup(RED"✗ - not found"NC);
	else if (last_exit & CANT_OPEN_OUTFILE)
		last_status = ft_strdup(RED"✗ - can't open outfile"NC);
	else if (last_exit & CANT_OPEN_INFILE)
		last_status = ft_strdup(RED"✗ - can't open infile"NC);
	else
		last_status = ft_strdup("N/A");
	return (last_status);
}
