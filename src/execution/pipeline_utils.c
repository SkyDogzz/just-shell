/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:28:10 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 22:33:06 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int	exec_left_child(t_btree *node, t_list *env, int fd_in, int pipe_fds[2])
{
	pid_t	left_pid;

	if (((t_leaf *)node->left->content)->type != NODE_WORD)
		return (destop_turbo(pipe_fds), -1);
	left_pid = fork();
	if (left_pid == 0)
	{
		close(pipe_fds[PIPE_LEFT]);
		ft_exec_with_redirects(((t_leaf *)node->left->content)->cmd, env, fd_in,
			pipe_fds[PIPE_RIGHT]);
		close(pipe_fds[PIPE_RIGHT]);
		exit(EXIT_SUCCESS);
	}
	if (left_pid < 0)
		return (destop_turbo(pipe_fds), -1);
	return (left_pid);
}

int	handle_right_word_node(t_btree *node, t_list *env, int pipe_fd,
		pid_t left_pid)
{
	pid_t	right_pid;
	int		status;

	right_pid = fork();
	if (right_pid == 0)
		ft_exec_with_redirects(((t_leaf *)node->right->content)->cmd, env,
			pipe_fd, STDOUT_FILENO);
	if (right_pid < 0)
	{
		close(pipe_fd);
		waitpid(left_pid, &status, 0);
		return (-1);
	}
	close(pipe_fd);
	waitpid(right_pid, &status, 0);
	g_exit = status;
	return (WEXITSTATUS(status));
}

int	handle_right_node(t_btree *node, t_list *env, int pipe_fd, pid_t left_pid)
{
	int	status;

	status = ft_exec_pipeline(node->right, env, pipe_fd);
	waitpid(left_pid, &status, 0);
	g_exit = status;
	return (WEXITSTATUS(status));
}
