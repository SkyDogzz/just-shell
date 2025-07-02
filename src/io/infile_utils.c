/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:36:42 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/02 19:00:05 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"

static int	open_tmp_write(char **filename)
{
	int	fd;

	*filename = get_tmp_fd();
	fd = open(*filename, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		free(*filename);
		return (-1);
	}
	return (fd);
}

static bool	handle_redirections(t_cmd *cmd, int fd, char *filename)
{
	while (cmd->redir)
	{
		if (!ft_redir_all(cmd, fd, filename))
			return (false);
	}
	return (true);
}

static bool	replace_stdin_with_tmp(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	dup2v2(fd, STDIN_FILENO);
	ft_close(&fd);
	return (true);
}

static bool	redir_in(t_list *redirs)
{
	t_redir	*redir;

	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == REDIR_HEREDOC || redir->type == REDIR_INPUT)
			return (true);
		redirs = redirs->next;
	}
	return (false);
}

int	ft_infile_exec(t_cmd *cmd)
{
	int		fd;
	char	*filename;
	t_list	*redir;

	redir = cmd->redir;
	if (!cmd->redir || !redir_in(redir))
		return (1);
	fd = open_tmp_write(&filename);
	if (fd < 0)
		return (0);
	if (!handle_redirections(cmd, fd, filename))
	{
		free(filename);
		return (0);
	}
	ft_close(&fd);
	if (!replace_stdin_with_tmp(filename))
	{
		free(filename);
		return (0);
	}
	unlink(filename);
	free(filename);
	cmd->redir = redir;
	return (2);
}
