/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <tstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:00:01 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 06:41:42 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler(const int signal)
{
	if (signal == SIGINT)
	{
		g_exit = SIGINT;
		rl_done = 1;
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_set_sigaction_no_inter(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, NULL);
}

void	ft_set_sigaction(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

bool	handle_sigint(void)
{
	if (g_exit == SIGINT)
	{
		g_exit = 0;
		return (true);
	}
	return (false);
}
