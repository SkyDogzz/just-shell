/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:22:10 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/17 16:07:10 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"

void	store_fd(int fd[4])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
	fd[3] = -1;
}

void	restore_fd(int fd[4])
{
	if (fd[0] >= 0)
		dup2(fd[0], STDIN_FILENO);
	if (fd[1] >= 0)
		dup2(fd[1], STDOUT_FILENO);
	if (fd[2] >= 0)
		dup2(fd[2], STDERR_FILENO);
	ft_close(&fd[0]);
	ft_close(&fd[1]);
	ft_close(&fd[2]);
	if (fd[3] > 0)
		ft_close(&fd[3]);
}
