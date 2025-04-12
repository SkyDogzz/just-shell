/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethostname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:11:23 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 16:46:26 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

char	*ft_gethostname(void)
{
	char	*hostname;
	int		hostname_file;
	int		i;
	char	**hostname_split;

	hostname_file = open("/etc/hostname", O_RDONLY);
	if (hostname_file == -1)
		return (NULL);
	hostname = ft_get_next_line(hostname_file);
	close(hostname_file);
	if (!hostname)
		return (NULL);
	hostname_split = ft_split(hostname, '.');
	free(hostname);
	if (!hostname_split || !hostname_split[0])
		return (NULL);
	hostname = ft_strdup(hostname_split[0]);
	i = 0;
	while (hostname_split[i])
		free(hostname_split[i++]);
	free(hostname_split);
	return (hostname);
}
