/* ************************************************************************** */
/*                                                                            */
/*                                             	_____                         */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                             | |  | |/ _ \ / _` |_  |_  /   */
/*   By: tstephan <thomas.stephan@live.fr>     | |__| | (_) | (_| |/ / / /    */
/*                                             |_____/ \___/ \__, /___/___|   */
/*   Created: 2025/01/10 17:00:01 by tstephan                 __/ |           */
/*   Updated: 2025/02/25 15:56:12 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig;

static void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		rl_done = 1;
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_set_sigaction(void)
{
	g_sig = 0;
	signal(SIGINT, ft_signal_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
