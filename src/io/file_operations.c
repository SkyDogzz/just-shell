/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:47:20 by yandry            #+#    #+#             */
/*   Updated: 2025/06/12 15:31:46 by tstephan         ###   ########.fr       */
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
	fd[0] = -2;
	fd[1] = -2;
	fd[2] = -2;
	fd[3] = -2;
	fd[4] = -2;
}
