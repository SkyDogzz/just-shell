/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:47:20 by yandry            #+#    #+#             */
/*   Updated: 2025/06/25 19:05:49 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include <unistd.h>

bool	ft_close(int *fd)
{
	if (*fd < 0)
		return (false);
	if (close(*fd) == -1)
		return (false);
	*fd = -1;
	return (true);
}

void	init_fds(int fd[5])
{
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd[3] = -1;
	fd[4] = -1;
}
