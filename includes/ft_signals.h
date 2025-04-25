/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:22:35 by yandry            #+#    #+#             */
/*   Updated: 2025/04/25 19:51:06 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNALS_H
# define FT_SIGNALS_H

# include <signal.h>
# include <stdbool.h>

typedef struct s_signal
{
	const int		sig_no;
	const char		*sig_name;
}	t_signal;

static const t_signal	g_signals[] = {
{SIGHUP, "SIGHUP"},
{SIGINT, "SIGINT"},
{SIGQUIT, "SIGQUIT"},
{SIGILL, "SIGILL"},
{SIGSEGV, "SIGSEGV"}
};

const char	*get_signal_name(int sig_no);
const char	*get_exited_status(void);
const char	*get_signaled_status(void);

void	ft_set_sigaction(void);
bool	handle_sigint(void);

#endif
