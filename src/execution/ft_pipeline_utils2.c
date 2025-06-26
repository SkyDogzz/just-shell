/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 01:57:40 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/26 16:35:00 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

static int	get_fd(t_redir *redir)
{
	int	flags;
	int	newfd;

	flags = 0;
	if (redir->type == REDIR_TRUNC_STDOUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redir->type == REDIR_APPEND_STDOUT)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (redir->type == REDIR_TRUNC_STDERR)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redir->type == REDIR_APPEND_STDERR)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (redir->type == REDIR_TRUNC_STDALL)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redir->type == REDIR_APPEND_STDALL)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	newfd = open(redir->file, flags, 0644);
	return (newfd);
}

static void	dup_fd(t_redir *redir, int newfd)
{
	if (redir->type == REDIR_INPUT)
		dup2v2(newfd, STDIN_FILENO);
	else if (redir->type == REDIR_TRUNC_STDOUT
		|| redir->type == REDIR_APPEND_STDOUT)
		dup2v2(newfd, STDOUT_FILENO);
	else if (redir->type == REDIR_TRUNC_STDERR
		|| redir->type == REDIR_APPEND_STDERR)
		dup2v2(newfd, STDERR_FILENO);
	else if (redir->type == REDIR_TRUNC_STDALL
		|| redir->type == REDIR_APPEND_STDALL)
	{
		dup2v2(newfd, STDOUT_FILENO);
		dup2v2(newfd, STDERR_FILENO);
	}
}

int	io_to_pipe(t_redir *redir)
{
	int	newfd;

	if (redir->type == REDIR_INPUT)
	{
		newfd = open(redir->file, O_RDONLY);
		if (newfd < 0)
		{
			ft_dprintf(STDERR_FILENO, CANT_OPEN_INFILE_PROMPT, redir->file);
			return (127);
		}
	}
	else
	{
		newfd = get_fd(redir);
		if (newfd < 0)
		{
			ft_dprintf(STDERR_FILENO, CANT_OPEN_OUTFILE_PROMPT, redir->file);
			return (127);
		}
	}
	dup_fd(redir, newfd);
	close(newfd);
	return (0);
}
