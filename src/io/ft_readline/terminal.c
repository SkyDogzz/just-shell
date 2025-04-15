/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:10:54 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 23:15:06 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	setup_terminal(t_readline *rl)
{
	struct termios	new_term;

	if (tcgetattr(STDIN_FILENO, &rl->old_term) == -1)
		return (0);
	new_term = rl->old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == -1)
		return (0);
	return (1);
}

void	restore_terminal(t_readline *rl)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &rl->old_term);
}
