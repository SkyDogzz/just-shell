/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:22:20 by yandry            #+#    #+#             */
/*   Updated: 2025/04/13 17:36:57 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	out_char(
			char character,
			void *buffer,
			size_t index,
			size_t n)
{
	(void)buffer;
	(void)index;
	(void)n;
	if (character)
		ft_putchar_fd(character, STDOUT_FILENO);
}

int	ft_printf(const char *format, ...)
{
	size_t		len;
	t_printf	int_printf;
	va_list		args;
	char		buff[1];

	if (!format)
		return (-1);
	va_start(args, format);
	int_printf.format = (char *)format;
	int_printf.buffer = buff;
	int_printf.max_len = (size_t)-1;
	int_printf.out = out_char;
	va_copy(int_printf.va, args);
	len = ft_vsnprintf(int_printf);
	va_end(args);
	return ((int)len);
}
