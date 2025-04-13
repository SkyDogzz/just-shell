/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_processor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:56:20 by yandry            #+#    #+#             */
/*   Updated: 2025/04/13 17:00:03 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	process_base_r(unsigned long val, t_printf *args, size_t index,
						const char *base)
{
	char	digit;
	size_t	base_len;

	base_len = ft_strlen(base);
	if (val < base_len)
	{
		digit = base[val];
		args->out(digit, args->buffer, index++, args->max_len);
		return (index);
	}
	index = process_base_r(val / base_len, args, index, base);
	digit = base[val % base_len];
	args->out(digit, args->buffer, index++, args->max_len);
	return (index);
}

static int	process_number_r(int val, t_printf *args, size_t index)
{
	if (val < 0)
	{
		args->out('-', args->buffer, index++, args->max_len);
		if (val == INT_MIN)
		{
			args->out('2', args->buffer, index++, args->max_len);
			return (process_number_r(147483648, args, index));
		}
		return (process_number_r(-val, args, index));
	}
	if (val < 10)
	{
		args->out(val + '0', args->buffer, index++, args->max_len);
		return (index);
	}
	index = process_number_r(val / 10, args, index);
	args->out((val % 10) + '0', args->buffer, index++, args->max_len);
	return (index);
}

int	process_dec(t_printf *args, size_t index, bool unsig)
{
	int	val;

	val = va_arg(args->va, int);
	if (val == 0)
	{
		args->out('0', args->buffer, index++, args->max_len);
		return (index);
	}
	if (!unsig)
		return (process_number_r(val, args, index));
	return (process_base_r(val, args, index, "0123456789"));
}

int	process_pointer(t_printf *args, size_t index)
{
	void			*ptr;
	unsigned long	val;

	ptr = va_arg(args->va, void *);
	if (!ptr)
		return (process_string(args, index, true));
	args->out('0', args->buffer, index++, args->max_len);
	args->out('x', args->buffer, index++, args->max_len);
	val = (unsigned long)ptr;
	if (!val)
	{
		args->out('0', args->buffer, index++, args->max_len);
		return (index);
	}
	return (process_base_r(val, args, index, "0123456789abcdef"));
}

int	process_hex(t_printf *args, size_t index)
{
	unsigned long	val;

	val = va_arg(args->va, unsigned long);
	if (val == 0)
	{
		args->out('0', args->buffer, index++, args->max_len);
		return (index);
	}
	if (*(args->format) == 'X')
		return (process_base_r(val, args, index, "0123456789ABCDEF"));
	else
		return (process_base_r(val, args, index, "0123456789abcdef"));
}
