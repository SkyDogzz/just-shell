/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuyau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:09:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 22:33:34 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int	setup_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		return (-1);
	return (0);
}

void	destop_turbo(int pipe_fds[2])
{
	if (pipe_fds[0] >= 0)
		close(pipe_fds[0]);
	if (pipe_fds[1] >= 0)
		close(pipe_fds[1]);
}
