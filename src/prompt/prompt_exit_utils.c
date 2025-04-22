/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_exit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:56:13 by yandry            #+#    #+#             */
/*   Updated: 2025/04/21 23:24:01 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_signals.h"

const char	*get_signal_name(int sig_no)
{
	int	i;

	i = 0;
	while (g_signals[i].sig_no)
	{
		if (g_signals[i].sig_no == sig_no)
			return (g_signals[i].sig_name);
		i++;
	}
	return ("N/A");
}

const char	*get_exited_status(void)
{
	char		*exit;
	char		*failure;
	char		*temp;
	const char	*last_status;

	exit = ft_itoa(WEXITSTATUS(g_exit));
	if (g_exit > 0)
	{
		temp = ft_strjoin(RED, "✗ - ");
		failure = ft_strjoin(temp, exit);
		free(temp);
		temp = ft_strdup(failure);
		free(failure);
	}
	else
		temp = ft_strjoin(GREEN, "✓");
	last_status = ft_strjoin(temp, NC);
	free(temp);
	free(exit);
	return (last_status);
}

const char	*get_signaled_status(void)
{
	char		*exit;
	char		*temp;
	char		*failure;
	const char	*last_status;

	exit = ft_strdup(get_signal_name(WTERMSIG(g_exit)));
	temp = ft_strjoin(ORANGE, "🗲 - ");
	failure = ft_strjoin(temp, exit);
	free(temp);
	temp = ft_strdup(failure);
	free(failure);
	free(exit);
	last_status = ft_strjoin(temp, NC);
	free(temp);
	return (last_status);
}

const char	*get_prompt_last_exit(void)
{
	const char	*last_status;

	if (WIFEXITED(g_exit))
		last_status = get_exited_status();
	else if (WIFSIGNALED(g_exit))
		last_status = get_signaled_status();
	else if (g_exit & CMD_NOT_FOUND_FLAG)
		last_status = ft_strdup(RED"✗ - not found"NC);
	else
		last_status = ft_strdup("N/A");
	return (last_status);
}
