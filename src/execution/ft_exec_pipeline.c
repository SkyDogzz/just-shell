/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:26:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/25 19:08:40 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

static int	handle_simple_node(t_context *context, int in_fd)
{
	int		status;
	pid_t	pid;

	pid = run_child(context, in_fd, STDOUT_FILENO, -1);
	if (in_fd != STDIN_FILENO)
		ft_close(&in_fd);
	waitpid(pid, &status, 0);
	return (status);
}

int	handle_pipe_node(t_context *context, int in_fd)
{
	int		fd[2];
	pid_t	pid;
	t_btree	*mem;
	int		status;

	if (pipev2(fd) == -1)
		return (127);
	mem = context->context;
	context->context = mem->left;
	pid = run_child(context, in_fd, fd[1], fd[0]);
	operate_on_pid_list(OP_INSERT, pid);
	ft_close(&fd[1]);
	if (in_fd != STDIN_FILENO)
		ft_close(&in_fd);
	context->context = mem->right;
	status = launch_recursive(context, fd[0]);
	ft_close(&fd[0]);
	wait_all();
	return (status);
	(void)pid;
}

int	launch_recursive(t_context *context, int in_fd)
{
	t_leaf	*leaf;

	if (!context)
		return (0);
	leaf = context->context->content;
	if (leaf->type != NODE_PIPE)
		return (handle_simple_node(context, in_fd));
	return (handle_pipe_node(context, in_fd));
}

int	ft_exec_pipeline(t_context *context, int *status)
{
	if (!context || !context->context)
		return (0);
	if (((t_leaf *)context->context->content)->type == NODE_PIPE)
		*status = launch_recursive(context, STDIN_FILENO);
	return (*status);
}
