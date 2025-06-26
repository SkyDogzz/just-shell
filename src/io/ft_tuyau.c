/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuyau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:09:29 by yandry            #+#    #+#             */
/*   Updated: 2025/06/26 16:38:46 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_io.h"

int	setup_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		ft_dprintf(STDERR_FILENO, "pipe creation failed");
		return (-1);
	}
	return (0);
}

void	destop_turbo(int pipe_fds[2])
{
	if (pipe_fds[0] >= 0)
	{
		if (!ft_close(&pipe_fds[PIPE_LEFT]))
			ft_dprintf(STDERR_FILENO, "failed to close pipe_fds[PIPE_LEFT]");
	}
	if (pipe_fds[1] >= 0)
	{
		if (!ft_close(&pipe_fds[PIPE_RIGHT]))
			ft_dprintf(STDERR_FILENO, "failed to close pipe_fds[PIPE_RIGHT]");
	}
}
