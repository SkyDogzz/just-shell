/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuyau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:09:29 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 06:27:42 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_io.h"

int	setup_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe creation failed");
		return (-1);
	}
	return (0);
}

void	destop_turbo(int pipe_fds[2])
{
	if (pipe_fds[0] >= 0)
	{
		if (!ft_close(&pipe_fds[PIPE_LEFT]))
			perror("failed to close pipe_fds[PIPE_LEFT]");
	}
	if (pipe_fds[1] >= 0)
	{
		if (!ft_close(&pipe_fds[PIPE_RIGHT]))
			perror("failed to close pipe_fds[PIPE_RIGHT]");
	}
}
