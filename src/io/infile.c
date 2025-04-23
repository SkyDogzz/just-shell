/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:09:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/23 02:42:00 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_heredoc(t_cmd *cmd, int fd)
{
	ft_putstr_fd(((t_redir *)cmd->redir->content)->file, fd);
	ft_putstr_fd("\n", fd);
}

static bool	ft_redir_input(t_cmd *cmd, int fd, char *filename)
{
	char	*buffer;
	int		fd2;

	fd2 = open(((t_redir *)cmd->redir->content)->file, O_RDONLY);
	if (fd2 < 0)
	{
		ft_putstr_fd("ssh-xx: can't open file ('", 1);
		ft_putstr_fd(((t_redir *)cmd->redir->content)->file, 1);
		ft_putendl_fd("')", 1);
		unlink(filename);
		close(fd);
		return (false);
	}
	buffer = ft_get_next_line(fd2);
	while (buffer)
	{
		buffer = ft_get_next_line(fd2);
		ft_putstr_fd(buffer, fd);
		free(buffer);
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

void	ft_infile_exec(t_cmd *cmd)
{
	int		fd;
	char	*filename;
	t_list	*redir;

	redir = cmd->redir;
	if (cmd->redir)
	{
		filename = get_tmp_fd();
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
			return ;
		while (cmd->redir)
			if (!ft_redir_all(cmd, fd, filename))
				exit(127);
		close(fd);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return ;
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(filename);
		free(filename);
	}
	cmd->redir = redir;
}
