/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/21 20:13:12 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	g_fd;

void	out_fd(	char character,
			void *buffer,
			size_t index,
			size_t n)
{
	(void)buffer;
	(void)index;
	(void)n;
	if (character)
		ft_putchar_fd(character, g_fd);
	
}


int	ft_dprintf(int fd, const char *format, ...)
{
	size_t		len;
	t_printf	int_printf;
	va_list		args;
	char		buff[1];

	if (!format)
		return (-1);
	va_start(args, format);
	g_fd = fd;
	int_printf.format = (char *)format;
	int_printf.buffer = buff;
	int_printf.max_len = (size_t)-1;
	int_printf.out = out_fd;
	va_copy(int_printf.va, args);
	len = ft_vsnprintf(int_printf);
	va_end(args);
	return ((int)len);

}
