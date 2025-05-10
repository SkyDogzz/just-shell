/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:22:10 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/09 17:05:25 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_fd(int fd[2])
{
	fd[0] = dup(STDOUT_FILENO);
	fd[1] = dup(STDERR_FILENO);
}

static void	ft_close(int fd)
{
	close(fd);
	printf("closed %d\n", fd);
}

void	restore_fd(int fd[4])
{
	dup2(fd[0], STDOUT_FILENO);
	dup2(fd[1], STDERR_FILENO);
	ft_close(fd[0]);
	ft_close(fd[1]);
	if (fd[2] > 0)
		ft_close(fd[2]);
	if (fd[3] > 0)
		ft_close(fd[3]);
}
