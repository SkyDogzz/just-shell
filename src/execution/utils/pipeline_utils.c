/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:28:10 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 09:55:37 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_io.h"
#include "minishell.h"

static int	close_wait_and_die(int pipe_fd, int *status, pid_t pid)
{
	ft_close(&pipe_fd);
	waitpid(pid, status, 0);
	return (-1);
}

int	exec_left_child(t_btree *root, t_context *context,
					int fd_in, int pipe_fds[2])
{
	pid_t	left_pid;
	t_leaf	*leaf;

	if (!context || !context->root || !root || !root->content)
		return (-1);
	leaf = root->content;
	if (leaf->type != NODE_WORD)
		return (destop_turbo(pipe_fds), -1);
	if (!ft_cmd_exists(leaf->cmd, context->env))
		return (destop_turbo(pipe_fds), -1);
	left_pid = fork();
	if (left_pid == 0)
	{
		close(context->fdin);
		close(context->fdout);
		ft_close(&pipe_fds[PIPE_LEFT]);
		ft_exec_with_redirects(((t_leaf *)root->content)->cmd,
			context->env, fd_in, pipe_fds[PIPE_RIGHT]);
		ft_free_context(context, true);
		exit(EXIT_SUCCESS);
	}
	if (left_pid < 0)
		return (destop_turbo(pipe_fds), -1);
	ft_close(&pipe_fds[PIPE_RIGHT]);
	return (left_pid);
}

int	handle_right_word_node(t_context *context, int pipe_fd,
		pid_t left_pid)
{
	pid_t	right_pid;
	int		status;
	t_leaf	*leaf;

	status = 0;
	if (!context || !context->root)
		return (close_wait_and_die(pipe_fd, &status, left_pid));
	leaf = context->root->right->content;
	if (!ft_cmd_exists(leaf->cmd, context->env))
		return (close_wait_and_die(pipe_fd, &status, left_pid));
	right_pid = fork();
	if (right_pid == 0)
	{
		close(context->fdin);
		close(context->fdout);
		ft_exec_with_redirects(((t_leaf *)context->root->right->content)->cmd,
			context->env, pipe_fd, STDOUT_FILENO);
		ft_free_context(context, true);
		exit(EXIT_SUCCESS);
	}
	if (right_pid < 0)
		return (close_wait_and_die(pipe_fd, &status, left_pid));
	ft_close(&pipe_fd);
	waitpid(right_pid, &status, 0);
	waitpid(left_pid, NULL, 0);
	return (status);
}

int	handle_right_node(t_context *context, int pipe_fd, pid_t left_pid)
{
	int	status;

	status = ft_exec_pipeline(context);
	free(context);
	ft_close(&pipe_fd);
	waitpid(left_pid, &status, 0);
	return (status);
}
