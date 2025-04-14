/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuyau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:09:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/14 17:11:45 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	setup_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		return (-1);
	return (0);
}

void	cleanup_pipe(int pipe_fds[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}
