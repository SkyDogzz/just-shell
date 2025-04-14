/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:35:32 by yandry            #+#    #+#             */
/*   Updated: 2025/04/13 17:42:16 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdbool.h>

static inline void	out_null(
					char character,
					void *buffer,
					size_t index,
					size_t max_len)
{
	(void)character;
	(void)buffer;
	(void)index;
	(void)max_len;
}

static int	evaluate_format_specifier(t_printf *args, size_t index)
{
	char	c;

	if (!args || !args->format || !(*args->format))
		return (index);
	(args->format)++;
	if (!(*args->format))
		return (index);
	c = *(args->format);
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
		index = process_number(args, index);
	else if (c == 'c')
		index = process_char(args, index);
	else if (c == 's')
		index = process_string(args, index, false);
	else if (c == 'p')
		index = process_pointer(args, index);
	else if (c == '%')
		args->out('%', args->buffer, index++, args->max_len);
	else
		args->out(c, args->buffer, index++, args->max_len);
	(args->format)++;
	return (index);
}

int	ft_vsnprintf(t_printf printf_args)
{
	size_t	i;

	i = 0;
	if (!printf_args.buffer)
		printf_args.out = out_null;
	while (*(printf_args.format))
	{
		if (*(printf_args.format) != '%')
		{
			printf_args.out(*(printf_args.format), printf_args.buffer,
				i++, printf_args.max_len);
			printf_args.format++;
		}
		else
			i = evaluate_format_specifier(&printf_args, i);
	}
	if (i < printf_args.max_len)
		printf_args.out((char)0, printf_args.buffer, i, printf_args.max_len);
	else
		printf_args.out((char)0, printf_args.buffer,
			printf_args.max_len - 1U, printf_args.max_len);
	return ((int)i);
}
