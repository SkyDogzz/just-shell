/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:09:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/22 17:21:00 by tstephan         ###   ########.fr       */
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
	if (fd2 <= 0)
	{
		ft_putstr_fd("ssh-xx: can't open file ('", 1);
		ft_putstr_fd(((t_redir *)cmd->redir->content)->file, 1);
		ft_putendl_fd("')", 1);
		close(fd);
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

void	ft_infile_exec(t_cmd *cmd)
{
	int	fd;

	if (cmd->redir)
	{
		fd = open("./a", O_CREAT | O_WRONLY, 0644);
		while (cmd->redir)
		{
			if (((t_redir *)cmd->redir->content)->type != REDIR_INPUT
				&& ((t_redir *)cmd->redir->content)->type != REDIR_HEREDOC)
			{
				cmd->redir = cmd->redir->next;
				continue ;
			}
			if (((t_redir *)cmd->redir->content)->type == REDIR_INPUT)
				ft_redir_input(cmd, fd);
			else
				ft_redir_heredoc(cmd, fd);
			cmd->redir = cmd->redir->next;
		}
		close(fd);
		fd = open("./a", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink("./a");
	}
}
