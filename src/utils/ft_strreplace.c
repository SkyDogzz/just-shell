/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:30:26 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 18:07:06 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

char	*ft_strreplace(const char *full, const char *old, const char *ne)
{
	char	*replaced;
	int		len;
	int		pos;

	if (!full || !old || !ne)
		return (NULL);
	if (!ft_strnstr(full, old, ft_strlen(full)))
		return (ft_strdup(full));
	len = ft_strlen(full) - ft_strlen(old) + ft_strlen(ne);
	replaced = (char *)malloc(sizeof(char) * (len + 1));
	if (!replaced)
		return (NULL);
	ft_bzero(replaced, len + 1);
	pos = 0;
	while (ft_strncmp(full, old, ft_strlen(old)) != 0)
		replaced[pos++] = *full++;
	if (!*full)
		return (replaced);
	full += ft_strlen(old);
	while (*ne)
		replaced[pos++] = *ne++;
	while (*full)
		replaced[pos++] = *full++;
	return (replaced);
}
