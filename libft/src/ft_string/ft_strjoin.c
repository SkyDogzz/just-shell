/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:06:06 by yandry            #+#    #+#             */
/*   Updated: 2025/04/13 11:16:03 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	char	*ptr;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	ptr = new;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (new);
}

char	*ft_strmultijoin(const char **strs, size_t elem_count)
{
	char	*new;
	char	*ptr;
	size_t	total_len;
	size_t	i;
	size_t	len;

	if (!strs)
		return (NULL);
	i = 0;
	total_len = 0;
	while (i < elem_count && strs[i])
		total_len += ft_strlen(strs[i++]);
	new = ft_calloc(total_len + 1, sizeof(char));
	if (!new)
		return (NULL);
	ptr = new;
	i = 0;
	while (i < elem_count && strs[i])
	{
		len = ft_strlen(strs[i]);
		ft_memcpy(ptr, strs[i], len);
		ptr += len;
		i++;
	}
	return (new);
}
