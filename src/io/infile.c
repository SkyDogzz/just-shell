/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:09:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 12:21:45 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"

static void	ft_redir_heredoc(t_cmd *cmd, int fd)
{
	ft_putstr_fd(((t_redir *)cmd->redir->content)->file, fd);
	ft_putstr_fd("\n", fd);
}

static bool	ft_check_fd(int fd, t_cmd *cmd)
{
	struct stat	sb;

	if (fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "ssh-xx: %s ('%s')\n",
			strerror(errno), ((t_redir *)cmd->redir->content)->file);
		return (false);
	}
	if (fstat(fd, &sb) != 0 || S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("ssh-xx: ('", 1);
		ft_putstr_fd(((t_redir *)cmd->redir->content)->file, 1);
		ft_putendl_fd("') is a directory", 1);
		return (false);
	}
	return (true);
}

static bool	ft_redir_input(t_cmd *cmd, int fd, char *filename)
{
	char		*buffer;
	int			fd2;

	fd2 = open(((t_redir *)cmd->redir->content)->file, O_RDONLY | O_CLOEXEC);
	if (!ft_check_fd(fd2, cmd))
	{
		unlink(filename);
		close(fd);
		return (false);
	}
	buffer = ft_get_next_line(fd2);
	while (buffer)
	{
		ft_putstr_fd(buffer, fd);
		free(buffer);
		buffer = ft_get_next_line(fd2);
	}
	close(fd2);
	return (true);
}

static bool	ft_redir_all(t_cmd *cmd, int fd, char *filename)
{
	if (((t_redir *)cmd->redir->content)->type != REDIR_INPUT
		&& ((t_redir *)cmd->redir->content)->type != REDIR_HEREDOC)
	{
		cmd->redir = cmd->redir->next;
		return (true);
	}
	if (((t_redir *)cmd->redir->content)->type == REDIR_INPUT)
	{
		if (!ft_redir_input(cmd, fd, filename))
			return (false);
	}
	else
		ft_redir_heredoc(cmd, fd);
	cmd->redir = cmd->redir->next;
	return (true);
}

bool	ft_infile_exec(t_cmd *cmd)
{
	int		fd;
	char	*filename;
	t_list	*redir;

	redir = cmd->redir;
	if (cmd->redir)
	{
		filename = get_tmp_fd();
		fd = open(filename, O_CREAT | O_WRONLY | O_CLOEXEC, 0644);
		if (fd < 0)
		{
			free(filename);
			return (false);
		}
		while (cmd->redir)
		{
			if (!ft_redir_all(cmd, fd, filename))
			{
				free(filename);
				return (false);
			}
		}
		ft_close(&fd);
		fd = open(filename, O_RDONLY | O_CLOEXEC);
		if (fd < 0)
		{
			free(filename);
			return (false);
		}
		dup2(fd, STDIN_FILENO);
		ft_close(&fd);
		unlink(filename);
		free(filename);
	}
	cmd->redir = redir;
	return (true);
}
