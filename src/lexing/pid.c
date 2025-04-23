/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 05:56:34 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/23 09:00:24 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_shell_pid(void)
{
	int		fd;
	char	*buffer;

	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
		return (0);
	buffer = (char *)malloc(sizeof(char) * 64);
	buffer = ft_get_next_line(fd);
	close(fd);
	return (ft_atoi(buffer));
}
