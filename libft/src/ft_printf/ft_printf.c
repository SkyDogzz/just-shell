/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:22:20 by yandry            #+#    #+#             */
/*   Updated: 2025/02/01 14:55:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(unsigned int n, char *set)
{
	static char	buffer[50];
	char		*ptr;
	int			base;

	base = ft_strlen(set);
	ptr = &buffer[49];
	*ptr = '\0';
	*--ptr = set[n % base];
	n /= base;
	while (n)
	{
		*--ptr = (n % base)[set];
		n /= base;
	}
	return (ptr);
}

// ah là là, sacrée norminette
// qu'est-ce qu'on RIGOLE bordel
static char	*ft_sinistre(char c, unsigned int n)
{
	if (c == 'u')
		return (ft_convert(n, "0123456789"));
	else if (c == 'x')
		return (ft_convert(n, "0123456789abcdef"));
	else if (c == 'X')
		return (ft_convert(n, "0123456789ABCDEF"));
	return ("");
}

// la tentation de malade de balancer un switch là dedans
// MAIS y a pas le droit :[
// du coup là je tank pour résister à mes demons internes
static int	ft_scan(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u' || c == 'x' || c == 'X')
		return (ft_putstr(ft_sinistre(c, va_arg(args, unsigned int))));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	va_start(args, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			len += ft_scan(*(format + 1), args);
			format += 2;
		}
		else
		{
			len += write(1, format, 1);
			format++;
		}
	}
	va_end(args);
	return (len);
}
