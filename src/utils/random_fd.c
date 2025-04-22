/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:02:23 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/22 19:33:47 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*bytes_to_nbr(char *bytes)
{
	char	*name;
	int		i;

	i = 0;
	name = (char *)ft_calloc(128, sizeof(char));
	while (i < 127)
	{
		name[i] = (bytes[i] % 5 + 5) + '0';
		i++;
	}
	free(bytes);
	return (name);
}

char	*get_tmp_fd(void)
{
	char	*bytes;
	int		fd;

	bytes = (char *)ft_calloc(128, sizeof(char));
	if (!bytes)
		return (NULL);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	read(fd, bytes, 127);
	if (!bytes)
		close(fd);
	return (bytes_to_nbr(bytes));
}
