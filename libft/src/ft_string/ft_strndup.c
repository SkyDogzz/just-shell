/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:12:32 by tstephan          #+#    #+#             */
/*   Updated: 2025/01/16 15:12:59 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, size_t size)
{
	char	*new;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	if (size < len)
		len = size;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && size--)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
