/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:03:29 by yandry            #+#    #+#             */
/*   Updated: 2024/12/11 13:46:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_puthex(unsigned long r)
{
	int	res;

	res = 0;
	if (r > 15)
		res += ft_puthex(r / 16);
	res += ft_putchar("0123456789abcdef"[r % 16]);
	return (res);
}

int	ft_putstr(const char *str)
{
	if (!str)
		return (ft_putstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putptr(void *ptr)
{
	unsigned long	ret;
	int				res;

	if (!ptr)
		return (ft_putstr("(nil)"));
	res = ft_putstr("0x");
	ret = (unsigned long)ptr;
	res += ft_puthex(ret);
	return (res);
}

int	ft_putnbr(int n)
{
	char	*num;
	int		len;

	len = 0;
	num = ft_itoa(n);
	len += ft_putstr(num);
	free(num);
	return (len);
}
