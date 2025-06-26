/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:27:45 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/26 07:33:03 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_io.h"

static int	here_to_stdin(const char *text)
{
	int	pfds[2];

	if (pipev2(pfds) == -1)
		return (127);
	write(pfds[1], text, ft_strlen(text));
	close(pfds[1]);
	dup2v2(pfds[0], STDIN_FILENO);
	close(pfds[0]);
	return (0);
}

int	manage_redir_child(t_context *context)
{
	t_leaf	*leaf;
	t_list	*r;
	t_redir	*redir;

	leaf = context->context->content;
	r = leaf->cmd->redir;
	while (r)
	{
		redir = r->content;
		if (redir->type == REDIR_HEREDOC && here_to_stdin(redir->file))
			return (127);
		else if (redir->type != REDIR_HEREDOC && io_to_pipe(redir))
			return (127);
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

int	run_child(t_context *context, int in_fd, int out_fd, int other_fd)
{
	pid_t	pid;
	int		status;
	t_leaf	*leaf;

	pid = fork();
	if (pid == 0)
	{
		ft_set_sigaction_inter();
		duppp(in_fd, out_fd, other_fd);
		leaf = context->context->content;
		if (leaf && leaf->type == NODE_WORD && leaf->cmd->redir)
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
