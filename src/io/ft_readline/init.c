/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:13:41 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 23:14:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	init_readline(t_readline *rl, const char *prompt)
{
	if (!setup_terminal(rl))
		return (0);
	if (prompt)
		write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	rl->buffer_size = BUFFER_SIZE;
	rl->buffer = ft_calloc(rl->buffer_size, sizeof(char));
	if (!rl->buffer)
	{
		restore_terminal(rl);
		return (0);
	}
	rl->buffer_pos = 0;
	rl->buffer[0] = '\0';
	return (1);
}
