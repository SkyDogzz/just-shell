/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:22:35 by yandry            #+#    #+#             */
/*   Updated: 2025/06/21 14:32:35 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNALS_H
# define FT_SIGNALS_H

# include <signal.h>

typedef struct s_signal
{
	const int		sig_no;
	const char		*sig_name;
	const char		*sig_desc;
}	t_signal;

typedef struct t_sig_pair
{
	char	signal_name[16];
	char	signal_description[32];
}	t_sig_pair;

static const t_signal	g_signals[] = {
{SIGHUP, "SIGHUP", "Hungup"},
{SIGINT, "SIGINT", "Interrupted"},
{SIGQUIT, "SIGQUIT", "Quitted"},
{SIGILL, "SIGILL", "Illegal instruction"},
{SIGTRAP, "SIGTRAP", "Trace/breakpoint trap"},
{SIGABRT, "SIGABRT", "Aborted"},
{SIGIOT, "SIGIOT", "IOT trap"},
{SIGBUS, "SIGBUS", "Bus error"},
{SIGFPE, "SIGFPE", "Floating point exception"},
{SIGKILL, "SIGKILL", "Killed"},
{SIGUSR1, "SIGUSR1", "User defined signal 1"},
{SIGSEGV, "SIGSEGV", "Segmentation  fault"},
{SIGUSR2, "SIGUSR2", "User defined signal 2"},
{SIGPIPE, "SIGPIPE", "Broken pipe"},
{SIGALRM, "SIGALRM", "Alarm clock"},
{SIGTERM, "SIGTERM", "Terminated"},
{SIGSTKFLT, "SIGSTKFLT", "Stack fault (@rparodi)"},
{SIGCHLD, "SIGCHLD", "Child status changed"},
{SIGCLD, "SIGCLD", "Child status changed"},
{SIGCONT, "SIGCONT", "Continued"},
{SIGSTOP, "SIGSTOP", "Stop"},
{SIGTSTP, "SIGTSTP", "Terminal stop"},
{SIGTTIN, "SIGTTIN", "Background read from TTY"},
{SIGTTOU, "SIGTTOU", "Background write from TTY"},
{SIGURG, "SIGURG", "Urgent condition on socket"},
{SIGXCPU, "SIGXCPU", "CPU limit exceeded"},
{SIGXFSZ, "SIGXFSZ", "File size limit exceeded"},
{SIGVTALRM, "SIGVTALRM", "Virtual alarm clock"},
{SIGPROF, "SIGPROF", "Profiling alarm clock"},
{SIGWINCH, "SIGWINCH", "Window size changed"},
{SIGIO, "SIGIO", "I/O now possible (yippie :D!!!)"},
{SIGPOLL, "SIGPOLL", "Pollable event"},
{SIGPWR, "SIGPWR", "Power failure"},
{SIGSYS, "SIGSYS", "Bad system call (oops)"},
{0, (char *)0, (char *)0}
};

const t_sig_pair	*get_signal(int sig_no);
void				set_sigpair(t_sig_pair *pair,
						const char *name, const char *desc);

#endif
