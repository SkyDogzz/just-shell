/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_processor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:22:21 by yandry            #+#    #+#             */
/*   Updated: 2025/04/13 17:22:32 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	process_number(t_printf *args, size_t index)
{
	char	f;

	if (!args || !args->format || !(*args->format))
		return (index);
	f = *(args->format);
	if (f == 'd' || f == 'i')
		return (process_dec(args, index, false));
	else if (f == 'u')
		return (process_dec(args, index, true));
	else if (f == 'x' || f == 'X')
		return (process_hex(args, index));
	return (index);
}

int	process_char(t_printf *args, size_t index)
{
	char	c;

	c = (char)va_arg(args->va, int);
	args->out(c, args->buffer, index++, args->max_len);
	return (index);
}

int	process_string(t_printf *args, size_t index, bool from_ptr)
{
	const char	*s;
	char		current;

	s = va_arg(args->va, char *);
	if (from_ptr)
		s = "(nil)";
	if (!s)
		s = "(null)";
	while (*s)
	{
		current = *s++;
		args->out(current, args->buffer, index++, args->max_len);
	}
	return (index);
}
