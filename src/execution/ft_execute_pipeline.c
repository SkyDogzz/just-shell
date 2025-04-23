/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/23 15:50:00 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_exec_with_redirects(t_cmd *cmd, t_list *env, int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	ft_subprocess(cmd, env);
	exit(EXIT_FAILURE);
}

static int	exec_pipe_node(t_btree *node, t_list *env, int fd_in)
{
	int		pipe_fds[2];
	pid_t	left_pid;

	if (setup_pipe(pipe_fds) == -1)
		return (-1);
	left_pid = exec_left_child(node, env, fd_in, pipe_fds);
	if (left_pid < 0)
		return (-1);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	close(pipe_fds[PIPE_RIGHT]);
	if (((t_leaf *)node->right->content)->type == NODE_WORD)
		return (handle_right_word_node(node, env,
				pipe_fds[PIPE_LEFT], left_pid));
	else
		return (handle_right_node(node, env, pipe_fds[PIPE_LEFT], left_pid));
}

int	ft_exec_pipeline(const t_btree *root, t_list *env, int fd_in)
{
	if (!root)
		return (0);
	if (((t_leaf *)root->content)->type == NODE_PIPE)
		return (WEXITSTATUS(exec_pipe_node((t_btree *)root, env, fd_in)));
	return (-1);
}
