/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:20:41 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 17:34:39 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_fd(int *fd)
{
	*fd = dup(STDOUT_FILENO);
}

void	restore_fd(int fd[2])
{
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

	fd = -1;
	while (cmd->redir)
	{
		if (((t_redir *)cmd->redir->content)->type == REDIR_TRUNC)
		{
			fd = open(((t_redir *)cmd->redir->content)->file, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (0);
		}
		if (((t_redir *)cmd->redir->content)->type == REDIR_APPEND)
		{
			fd = open(((t_redir *)cmd->redir->content)->file, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (0);
		}
		cmd->redir = cmd->redir->next;
	}
	if (fd < 0)
		return (fd);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}
