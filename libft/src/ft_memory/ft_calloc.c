/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:53:42 by yandry            #+#    #+#             */
/*   Updated: 2025/02/01 14:55:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_fill_zero(size_t size)
{
	void	*spuff;

	spuff = (void *)malloc(size);
	if (!spuff)
		return (NULL);
	return (ft_memset(spuff, 0, size));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	if (size != 0 && nmemb > ((size_t) - 1 / size))
		return (NULL);
	return (ft_fill_zero(nmemb * size));
}
