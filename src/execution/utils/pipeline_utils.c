/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:28:10 by yandry            #+#    #+#             */
/*   Updated: 2025/05/17 15:43:32 by yandry           ###   ########.fr       */
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

int	exec_left_child(t_btree *node, t_list *env, int fd_in, int pipe_fds[2])
{
	pid_t	left_pid;
	t_leaf	*leaf;

	if (!node || !node->left)
		return (-1);
	leaf = node->left->content;
	if (leaf->type != NODE_WORD)
		return (destop_turbo(pipe_fds), -1);
	if (!ft_cmd_exists(leaf->cmd, env))
		return (destop_turbo(pipe_fds), -1);
	left_pid = fork();
	if (left_pid == 0)
	{
		ft_close(&pipe_fds[PIPE_LEFT]);
		ft_exec_with_redirects(((t_leaf *)node->left->content)->cmd, env, fd_in,
			pipe_fds[PIPE_RIGHT]);
		exit(EXIT_SUCCESS);
	}
	if (left_pid < 0)
		return (destop_turbo(pipe_fds), -1);
	ft_close(&pipe_fds[PIPE_RIGHT]);
	return (left_pid);
}

int	handle_right_word_node(t_btree *node, t_list *env, int pipe_fd,
		pid_t left_pid)
{
	pid_t	right_pid;
	int		status;
	char	*path;
	int		saved_fds[4];

	status = 0;
	store_fd(saved_fds);
	path = ft_get_executable_path(((t_leaf *)node->right->content)->cmd, env);
	if (!path)
	{
		restore_fd(saved_fds);
		return (close_wait_and_die(pipe_fd, &status, left_pid));
	}
	free(path);
	right_pid = fork();
	if (right_pid == 0)
	{
		ft_exec_with_redirects(((t_leaf *)node->right->content)->cmd, env,
			pipe_fd, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (right_pid < 0)
	{
		restore_fd(saved_fds);
		return (close_wait_and_die(pipe_fd, &status, left_pid));
	}
	ft_close(&pipe_fd);
	waitpid(right_pid, &status, 0);
	waitpid(left_pid, NULL, 0);
	restore_fd(saved_fds);
	return (status);
}

int	handle_right_node(t_btree *node, t_list *env, int pipe_fd, pid_t left_pid)
{
	int	status;
	int	saved_fds[4];

	store_fd(saved_fds);
	status = ft_exec_pipeline(node->right, env, pipe_fd);
	ft_close(&pipe_fd);
	waitpid(left_pid, &status, 0);
	restore_fd(saved_fds);
	return (status);
}
