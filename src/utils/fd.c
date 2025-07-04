/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:22:10 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/26 16:37:30 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"

void	store_fd(int fd[5])
{
	fd[0] = dup(STDIN_FILENO);
	if (fd[0] == -1)
		ft_dprintf(STDERR_FILENO, "dup failed for STDIN");
	fd[1] = dup(STDOUT_FILENO);
	if (fd[1] == -1)
		ft_dprintf(STDERR_FILENO, "dup failed for STDOUT");
	fd[2] = dup(STDERR_FILENO);
	if (fd[2] == -1)
		ft_dprintf(STDERR_FILENO, "dup failed for STDERR");
}

void	restore_fd(int fd[5])
{
	dup2v2(fd[0], STDIN_FILENO);
	ft_close(&fd[0]);
	dup2v2(fd[1], STDOUT_FILENO);
	ft_close(&fd[1]);
	dup2v2(fd[2], STDERR_FILENO);
	ft_close(&fd[2]);
	ft_close(&fd[3]);
	ft_close(&fd[4]);
}
