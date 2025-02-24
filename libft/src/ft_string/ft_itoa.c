/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:20:00 by yandry            #+#    #+#             */
/*   Updated: 2025/02/01 14:55:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_size(long nb)
{
	size_t	size;

	size = 0;
	if (nb < 0)
	{
		nb = -nb;
		size = 1;
	}
	if (nb == 0)
		size = 1;
	else
	{
		while (nb)
		{
			nb /= 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*ptr;
	long	nb;
	size_t	size;

	nb = (long)n;
	size = ft_count_size(nb);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ptr = str + size;
	*ptr = '\0';
	if (nb < 0)
	{
		*str = '-';
		nb = -nb;
	}
	else if (nb == 0)
		*str = '0';
	while (nb)
	{
		*--ptr = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
