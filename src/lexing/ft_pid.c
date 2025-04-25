/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 05:56:34 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:18:49 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lex.h"

int	get_shell_pid(void)
{
	int		fd;
	char	*buffer;
	int		pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
		return (0);
	buffer = ft_get_next_line(fd);
	close(fd);
	pid = ft_atoi(buffer);
	free(buffer);
	return (pid);
}
