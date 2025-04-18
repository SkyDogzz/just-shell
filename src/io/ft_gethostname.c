/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethostname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:11:23 by yandry            #+#    #+#             */
/*   Updated: 2025/04/18 19:25:45 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static char	*set_hostname(char *hostname)
{
	char	*final;
	char	*user;

	user = getenv("USER");
	if (!hostname || ! user)
		return (NULL);
	if (ft_strncmp(user, "root", 4) == 0)
	{
		final = ft_calloc(ft_strlen(hostname) + 9, sizeof(char));
		if (!final)
			return (NULL);
		ft_snprintf(final, ft_strlen(hostname) + 8, "nasa (%s)", hostname);
		return (final);
	}
	return (ft_strdup(hostname));
}

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
	hostname = set_hostname(hostname_split[0]);
	i = 0;
	while (hostname_split[i])
		free(hostname_split[i++]);
	free(hostname_split);
	return (hostname);
}
