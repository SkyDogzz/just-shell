/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:36:42 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/26 04:03:30 by tstephan         ###   ########.fr       */
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

bool	ft_infile_exec(t_cmd *cmd)
{
	int		fd;
	char	*filename;
	t_list	*redir;

	redir = cmd->redir;
	if (!cmd->redir)
		return (true);
	fd = open_tmp_write(&filename);
	if (fd < 0)
		return (false);
	if (!handle_redirections(cmd, fd, filename))
	{
		free(filename);
		return (false);
	}
	ft_close(&fd);
	if (!replace_stdin_with_tmp(filename))
	{
		free(filename);
		return (false);
	}
	unlink(filename);
	free(filename);
	cmd->redir = redir;
	return (true);
}
