/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:30:05 by yandry            #+#    #+#             */
/*   Updated: 2025/02/01 14:55:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(const char chr)
{
	return (chr == 0x20
		|| chr == 0x0C
		|| chr == 0x0A
		|| chr == 0x0D
		|| chr == 0x09
		|| chr == 0x0B);
}

int	ft_atoi(const char *nptr)
{
	int	k;
	int	sign;

	k = 0;
	sign = 1;
	while (is_whitespace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -sign;
		nptr++;
	}
	while (ft_isdigit((int)*nptr))
		k = (k << 3) + (k << 1) + (*nptr++) - '0';
	return (k * sign);
}
