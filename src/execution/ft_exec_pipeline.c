/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:26:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 10:26:45 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

static int	run_child(t_contex2 *context, int in_fd, int out_fd, int other_fd)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (127);
	if (pid == 0)
	{
		ft_set_sigaction_no_inter();
		if (in_fd != STDIN_FILENO)
			dup2v2(in_fd, STDIN_FILENO);
		if (out_fd != STDOUT_FILENO)
			dup2v2(out_fd, STDOUT_FILENO);
		if (in_fd != STDIN_FILENO)
			ft_close(&in_fd);
		if (out_fd != STDOUT_FILENO)
			ft_close(&out_fd);
		if (other_fd >= 0 && other_fd != STDIN_FILENO
			&& other_fd != STDOUT_FILENO)
			ft_close(&other_fd);
		status = ft_exec(context);
		ft_free_context(context, true);
		exit(status);
	}
	return (pid);
}

static int	launch_recursive(t_contex2 *context, int in_fd)
{
	int		status;
	t_leaf	*leaf;
	pid_t	pid;
	int		fd[2];
	t_btree	*mem;

	if (!context)
		return (0);
	leaf = context->context->content;
	if (leaf->type != NODE_PIPE)
	{
		pid = run_child(context, in_fd, STDOUT_FILENO, -1);
		if (in_fd != STDIN_FILENO)
			ft_close(&in_fd);
		waitpid(pid, &status, 0);
		return (status);
	}
	if (pipev2(fd) == -1)
		return (127);
	mem = context->context;
	context->context = mem->left;
	pid = run_child(context, in_fd, fd[1], fd[0]);
	waitpid(pid, NULL, 0);
	ft_close(&fd[1]);
	if (in_fd != STDIN_FILENO)
		ft_close(&in_fd);
	context->context = mem->right;
	status = launch_recursive(context, fd[0]);
	ft_close(&fd[0]);
	return (status);
}

int	ft_exec_pipeline(t_contex2 *context, int *status)
{
	if (!context || !context->context)
		return (0);
	if (((t_leaf *)context->context->content)->type == NODE_PIPE)
		*status = launch_recursive(context, STDIN_FILENO);
	return (*status);
}
