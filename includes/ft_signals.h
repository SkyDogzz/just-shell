/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:22:35 by yandry            #+#    #+#             */
/*   Updated: 2025/06/20 22:17:48 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNALS_H
# define FT_SIGNALS_H

# include <signal.h>

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
{SIGTRAP, "SIGTRAP"},
{SIGABRT, "SIGABRT"},
{SIGIOT, "SIGIOT"},
{SIGBUS, "SIGBUS"},
{SIGFPE, "SIGFPE"},
{SIGKILL, "SIGKILL"},
{SIGUSR1, "SIGUSR1"},
{SIGSEGV, "SIGSEGV"},
{SIGUSR2, "SIGUSR2"},
{SIGPIPE, "SIGPIPE"},
{SIGALRM, "SIGALRM"},
{SIGTERM, "SIGTERM"},
{SIGSTKFLT, "SIGSTKFLT"},
{SIGCHLD, "SIGCHLD"},
{SIGCLD, "SIGCLD"},
{SIGCONT, "SIGCONT"},
{SIGSTOP, "SIGSTOP"},
{SIGTSTP, "SIGTSTP"},
{SIGTTIN, "SIGTTIN"},
{SIGTTOU, "SIGTTOU"},
{SIGURG, "SIGURG"},
{SIGXCPU, "SIGXCPU"},
{SIGXFSZ, "SIGXFSZ"},
{SIGVTALRM, "SIGVTALRM"},
{SIGPROF, "SIGPROF"},
{SIGWINCH, "SIGWINCH"},
{SIGIO, "SIGIO"},
{SIGPOLL, "SIGPOLL"},
{SIGPWR, "SIGPWR"},
{SIGSYS, "SIGSYS"},
{0, (char *)0}
};

const char	*get_signal_name(int sig_no);

#endif
