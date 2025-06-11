/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:20:41 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/11 18:08:53 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_open(const char *pathname, int flags, mode_t mode, int fd)
{
	if (fd != -1 && fd != -2)
		close(fd);
	fd = open(pathname, flags | O_CLOEXEC, mode);
	if (fd == -1)
		return (-1);
	return (fd);
}

static bool	open_trunc(t_redir *redir, int fd[5])
{
	if (redir->type == REDIR_TRUNC_STDOUT)
	{
		fd[3] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644, fd[3]);
		if (fd[3] == -1)
			return (false);
	}
	else if (redir->type == REDIR_TRUNC_STDERR)
	{
		fd[4] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644, fd[4]);
		if (fd[4] == -1)
			return (false);
	}
	else if (redir->type == REDIR_TRUNC_STDALL)
	{
		fd[3] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644, fd[3]);
		fd[4] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644, fd[4]);
		if (fd[3] == -1 || fd[4] == -1)
			return (false);
	}
	return (true);
}

static bool	open_append(t_redir *redir, int fd[5])
{
	if (redir->type == REDIR_APPEND_STDOUT)
	{
		fd[3] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644, fd[3]);
		if (fd[3] == -1)
			return (false);
	}
	else if (redir->type == REDIR_APPEND_STDERR)
	{
		fd[4] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644, fd[4]);
		if (fd[4] == -1)
			return (false);
	}
	else if (redir->type == REDIR_APPEND_STDALL)
	{
		fd[3] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644, fd[3]);
		fd[4] = close_open(redir->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644, fd[4]);
		if (fd[3] == -1 || fd[4] == -1)
			return (false);
	}
	return (true);
}

static bool	ft_ft(int fd[5], t_cmd *cmd, t_list *mem)
{
	if (!cmd->redir || !cmd->redir->content)
		return (true);
	if (fd[3] == 0 || fd[3] == -1 || fd[4] == 0 || fd[4] == -1)
	{
		ft_dprintf(fd[1], "ssh-xx: %s ('%s')\n",
			strerror(errno), ((t_redir *)cmd->redir->content)->file);
		restore_fd(fd);
		cmd->redir = mem;
		return (false);
	}
	return (true);
}

bool	open_outfile(t_cmd *cmd, int fd[5])
{
	t_redir	*redir;
	t_list	*mem;

	fd[3] = -2;
	fd[4] = -2;
	mem = cmd->redir;
	while (cmd->redir)
	{
		redir = (t_redir *)cmd->redir->content;
		if (!open_trunc(redir, fd) || !open_append(redir, fd))
		{
			cmd->redir = mem;
			return (false);
		}
		cmd->redir = cmd->redir->next;
	}
	printf("fd[2] %d\n", fd[2]);
	dup2(fd[3], STDOUT_FILENO);
	printf("fd[2] %d\n", fd[2]);
	dup2(fd[4], STDERR_FILENO);
	if (!ft_ft(fd, cmd, mem))
		return (false);
	cmd->redir = mem;
	return (true);
}
