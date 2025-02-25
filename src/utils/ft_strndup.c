/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:43:42 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/25 16:43:51 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	pos;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	pos = 0;
	while (s[pos] && n)
	{
		dup[pos] = s[pos];
		pos++;
		n--;
	}
	dup[pos] = 0;
	return (dup);
}
