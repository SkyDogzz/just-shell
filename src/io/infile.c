/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:09:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/22 19:16:41 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_heredoc(t_cmd *cmd, int fd)
{
	ft_putstr_fd(((t_redir *)cmd->redir->content)->file, fd);
	ft_putstr_fd("\n", fd);
}

static void	ft_redir_input(t_cmd *cmd, int fd)
{
	char	*buffer;
	int		fd2;

	fd2 = open(((t_redir *)cmd->redir->content)->file, O_RDONLY);
	if (fd2 < 0)
		return ;
	if (fd2 <= 0)
	{
		ft_putstr_fd("ssh-xx: can't open file ('", 1);
		ft_putstr_fd(((t_redir *)cmd->redir->content)->file, 1);
		ft_putendl_fd("')", 1);
		exit(127);
	}
	buffer = ft_get_next_line(fd2);
	while (buffer)
	{
		buffer = ft_get_next_line(fd2);
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
	close(fd2);
}

static void	ft_redir_all(t_cmd *cmd, int fd)
{
	if (((t_redir *)cmd->redir->content)->type != REDIR_INPUT
		&& ((t_redir *)cmd->redir->content)->type != REDIR_HEREDOC)
	{
		cmd->redir = cmd->redir->next;
		return ;
	}
	if (((t_redir *)cmd->redir->content)->type == REDIR_INPUT)
		ft_redir_input(cmd, fd);
	else
		ft_redir_heredoc(cmd, fd);
	cmd->redir = cmd->redir->next;
}

void	ft_infile_exec(t_cmd *cmd)
{
	int		fd;
	char	*filename;

	if (cmd->redir)
	{
		filename = get_tmp_fd();
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
		printf("lui = '%s'\n", filename);
		printf("1 %d\n", fd);
		if (fd < 0)
			return ;
		while (cmd->redir)
			ft_redir_all(cmd, fd);
		close(fd);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return ;
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(filename);
	}
}
