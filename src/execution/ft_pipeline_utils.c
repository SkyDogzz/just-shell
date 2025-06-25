/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:27:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/25 20:40:16 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_io.h"

int	manage_redir_child(t_contex2 *context)
{
	t_leaf	*leaf;
	t_list	*r;
	t_redir	*redir;
	int		newfd;
	int		flags;

	leaf = context->context->content;
	r = leaf->cmd->redir;
	while (r)
	{
		redir = r->content;
		if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
			newfd = open(redir->file, O_RDONLY);
		else
		{
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
		}
		if (newfd < 0)
			return (127);
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
		close(newfd);
		r = r->next;
	}
	return (0);
}

static void	duppp(int in_fd, int out_fd, int other_fd)
{
	if (in_fd != STDIN_FILENO)
		dup2v2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2v2(out_fd, STDOUT_FILENO);
	if (other_fd >= 0)
		ft_close(&other_fd);
	if (in_fd != STDIN_FILENO)
		ft_close(&in_fd);
	if (out_fd != STDOUT_FILENO)
		ft_close(&out_fd);
}

int	run_child(t_contex2 *context, int in_fd, int out_fd, int other_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_set_sigaction_no_inter();
		duppp(in_fd, out_fd, other_fd);
		if (((t_leaf *)context->context->content)->cmd->redir)
		{
			if (manage_redir_child(context))
			{
				ft_free_context(context, true);
				exit(127);
			}
		}
		status = ft_exec(context, false);
		ft_free_context(context, true);
		exit(status);
	}
	return (pid);
}
