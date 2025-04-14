/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:27:40 by yandry            #+#    #+#             */
/*   Updated: 2025/04/13 17:36:47 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	out_to_buffer(
			char character,
			void *buffer,
			size_t index,
			size_t n)
{
	if (index < n)
		((char *)buffer)[index] = character;
}

int	ft_snprintf(char *str, size_t n, const char *format, ...)
{
	size_t		len;
	t_printf	int_printf;
	va_list		args;

	if (!str || !format)
		return (-1);
	va_start(args, format);
	int_printf.format = (char *)format;
	int_printf.buffer = str;
	int_printf.max_len = n;
	int_printf.out = out_to_buffer;
	va_copy(int_printf.va, args);
	len = ft_vsnprintf(int_printf);
	va_end(args);
	return ((int)len);
}
