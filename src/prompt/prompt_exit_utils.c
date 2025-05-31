/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_exit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:56:13 by yandry            #+#    #+#             */
/*   Updated: 2025/05/27 16:34:26 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_signals.h"
#include <stdlib.h>

int	status = 1 << 8;

const char	*get_signal_name(int sig_no)
{
	int	i;

	i = 0;
	while (g_signals[i].sig_no && g_signals[i].sig_name)
	{
		if (g_signals[i].sig_no == sig_no)
			return (g_signals[i].sig_name);
		i++;
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
	else
		last_status = ft_strdup("N/A");
	return (last_status);
}
