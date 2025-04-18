/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:04:33 by yandry            #+#    #+#             */
/*   Updated: 2025/04/18 15:58:14 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include <stdio.h>

char	*resize_buffer(t_readline *rl)
{
	char	*new_buffer;
	size_t	new_size;

	new_size = rl->buffer_size * 2;
	new_buffer = ft_calloc(new_size, sizeof(char));
	if (!new_buffer)
		return (NULL);
	ft_memcpy(new_buffer, rl->buffer, rl->buffer_pos);
	free(rl->buffer);
	rl->buffer_size = new_size;
	return (new_buffer);
}

int	process_input(t_readline *rl)
{
	int		status;
	ssize_t	bytes_read;
	char	*new_buffer;

	bytes_read = read(STDIN_FILENO, &rl->c, 1);
	if (bytes_read <= 0)
		return (1);
	status = handle_special_chars(rl);
	if (status != 0)
		return (status);
	if (rl->buffer_pos >= rl->buffer_size - 2)
	{
		new_buffer = resize_buffer(rl);
		if (!new_buffer)
		{
			restore_terminal(rl);
			return (-1);
		}
		rl->buffer = new_buffer;
	}
	rl->buffer[rl->buffer_pos++] = rl->c;
	rl->buffer[rl->buffer_pos] = '\0';
	write(STDOUT_FILENO, &rl->c, 1);
	return (0);
}

char	*finalize_input(t_readline *rl, int status)
{
	char	*result;
	char	*trimmed;

	if (status < 0)
	{
		free(rl->buffer);
		rl->buffer = NULL;
		restore_terminal(rl);
		return (NULL);
	}
	rl->buffer[rl->buffer_pos] = '\0';
	trimmed = ft_strdup(rl->buffer);
	if (!trimmed)
	{
		free(rl->buffer);
		restore_terminal(rl);
		return (NULL);
	}
	write(STDOUT_FILENO, "\n", 1);
	free(rl->buffer);
	result = trimmed;
	restore_terminal(rl);
	return (result);
}

char	*readline(const char *prompt)
{
	t_readline	rl;
	int			status;
	char		*final_input;

	if (!init_readline(&rl, prompt))
		return (NULL);
	while (1)
	{
		status = process_input(&rl);
		if (status)
			break ;
	}
	final_input = finalize_input(&rl, status);
	if (final_input && final_input[0] == '\0')
	{
		free(final_input);
		return (ft_strdup(""));
	}
	return (final_input);
}
