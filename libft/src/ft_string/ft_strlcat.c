/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:11:26 by yandry            #+#    #+#             */
/*   Updated: 2024/12/11 13:46:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_len;
	size_t	pos;
	size_t	i;

	dst_len = ft_strlen(dst);
	pos = 0;
	while (dst[pos])
		pos++;
	i = 0;
	while (src[i] && (i + pos + 1) < n)
	{
		dst[pos + i] = src[i];
		i++;
	}
	if (i < n)
		dst[pos + i] = '\0';
	if (n <= dst_len)
		return (ft_strlen(src) + n);
	else
		return (ft_strlen(src) + dst_len);
}
