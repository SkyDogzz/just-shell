/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:09:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/26 04:14:13 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"

static void	ft_redir_heredoc(t_cmd *cmd, int fd)
{
	ft_putstr_fd(((t_redir *)cmd->redir->content)->file, fd);
	ft_putstr_fd("\n", fd);
}

static bool	ft_check_fd(int fd)
{
	struct stat	sb;

	if (fd < 0)
		return (false);
	if (fstat(fd, &sb) != 0 || S_ISDIR(sb.st_mode))
		return (false);
	return (true);
}

static bool	ft_redir_input(t_cmd *cmd, int fd, char *filename)
{
	char		*buffer;
	int			fd2;

	fd2 = open(((t_redir *)cmd->redir->content)->file, O_RDONLY);
	if (!ft_check_fd(fd2))
	{
		unlink(filename);
		ft_close(&fd);
		ft_close(&fd2);
		return (false);
	}
	buffer = ft_get_next_line(fd2);
	while (buffer)
	{
		ft_putstr_fd(buffer, fd);
		free(buffer);
		buffer = ft_get_next_line(fd2);
	}
	ft_close(&fd);
	ft_close(&fd2);
	return (true);
}

bool	ft_redir_all(t_cmd *cmd, int fd, char *filename)
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
