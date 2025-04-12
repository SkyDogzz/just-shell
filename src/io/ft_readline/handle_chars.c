/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:09:34 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 23:09:50 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	handle_backspace(t_readline *rl)
{
	if (rl->buffer_pos > 0)
	{
		rl->buffer_pos--;
		write(STDOUT_FILENO, "\b \b", 3);
	}
}

int	handle_special_chars(t_readline *rl)
{
	if (rl->c == '\n' || rl->c == '\r')
		return (1);
	if (rl->c == 127 || rl->c == 8)
	{
		handle_backspace(rl);
		return (2);
	}
	if (rl->c == 4 && rl->buffer_pos == 0)
		return (-1);
	return (0);
}
