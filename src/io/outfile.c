/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:20:41 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/29 15:44:25 by tstephan         ###   ########.fr       */
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
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (fd[2] > 0)
		close(fd[2]);
	if (fd[3] > 0)
		close(fd[3]);
}

static bool	open_trunc(t_redir *redir, int fd[4])
{
	if (redir->type == REDIR_TRUNC_STDOUT)
	{
		fd[2] = open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (fd[2] == -1)
			return (false);
	}
	else if (redir->type == REDIR_TRUNC_STDERR)
	{
		fd[3] = open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (fd[3] == -1)
			return (false);
	}
	else if (redir->type == REDIR_TRUNC_STDALL)
	{
		fd[2] = open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		fd[3] = open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (fd[2] == -1 || fd[3] == -1)
			return (false);
	}
	return (true);
}

static bool	open_append(t_redir *redir, int fd[4])
{
	if (redir->type == REDIR_APPEND_STDOUT)
	{
		fd[2] = open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (fd[2] == -1)
			return (false);
	}
	else if (redir->type == REDIR_APPEND_STDERR)
	{
		fd[3] = open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (fd[3] == -1)
			return (false);
	}
	else if (redir->type == REDIR_APPEND_STDALL)
	{
		fd[2] = open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		fd[3] = open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (fd[2] == -1 || fd[3] == -1)
			return (false);
	}
	return (true);
}

void	open_outfile(t_cmd *cmd, int fd[4])
{
	t_redir	*redir;

	fd[2] = -2;
	fd[3] = -2;
	while (cmd->redir)
	{
		redir = (t_redir *)cmd->redir->content;
		if (!open_trunc(redir, fd) || !open_append(redir, fd))
			return ;
		cmd->redir = cmd->redir->next;
	}
	dup2(fd[2], STDOUT_FILENO);
	dup2(fd[3], STDERR_FILENO);
}
