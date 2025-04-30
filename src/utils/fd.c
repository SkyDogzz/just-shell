/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:22:10 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/30 18:22:11 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_fd(int fd[2])
{
	fd[0] = dup(STDOUT_FILENO);
	fd[1] = dup(STDERR_FILENO);
}

void	restore_fd(int fd[4])
{
	dup2(fd[0], STDOUT_FILENO);
	dup2(fd[1], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (fd[2] > 0)
		close(fd[2]);
	if (fd[3] > 0)
		close(fd[3]);
}
