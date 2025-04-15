/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/15 15:54:36 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	execute_command(t_leaf *leaf, char **env)
{
	ft_subprocess(leaf->cmd, env);
	exit(EXIT_FAILURE);
}

static int	exec_pipe_left(const t_btree *node, char **env, int pipe_fds[2])
{
	t_leaf	*leaf;

	close(pipe_fds[0]);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
	{
		close(pipe_fds[1]);
		exit(EXIT_FAILURE);
	}
	close(pipe_fds[1]);
	if (node->left)
	{
		leaf = (t_leaf *)node->left->content;
		if (leaf->type == NODE_WORD)
			execute_command(leaf, env);
		else
			exit(ft_exec(node->left, env));
	}
	exit(EXIT_FAILURE);
}

static int	exec_pipe_right(const t_btree *node, char **env, int pipe_fds[2])
{
	t_leaf	*leaf;

	close(pipe_fds[1]);
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
	{
		close(pipe_fds[0]);
		exit(EXIT_FAILURE);
	}
	close(pipe_fds[0]);
	if (node->right)
	{
		leaf = (t_leaf *)node->right->content;
		if (leaf->type == NODE_WORD)
			execute_command(leaf, env);
		else
			exit(ft_exec(node->right, env));
	}
	exit(EXIT_FAILURE);
}

static pid_t	fork_pipe_process(const t_btree *node, char **env,
							int pipe_fds[2], int pipe_side)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (pipe_side == 0)
			exec_pipe_left(node, env, pipe_fds);
		else
			exec_pipe_right(node, env, pipe_fds);
	}
	return (pid);
}

int	ft_exec_pipeline(const t_btree *root, char **env)
{
	int		pipe_fds[2];
	pid_t	pids[2];
	int		statuses[2];

	if (setup_pipe(pipe_fds) == -1)
		return (-1);
	pids[0] = fork_pipe_process(root, env, pipe_fds, 0);
	if (pids[0] == -1)
	{
		destop_turbo(pipe_fds);
		return (-1);
	}
	pids[1] = fork_pipe_process(root, env, pipe_fds, 1);
	if (pids[1] == -1)
	{
		destop_turbo(pipe_fds);
		kill(pids[0], SIGTERM);
		waitpid(pids[0], NULL, 0);
		return (-1);
	}
	destop_turbo(pipe_fds);
	waitpid(pids[0], &statuses[0], 0);
	waitpid(pids[1], &statuses[1], 0);
	g_exit = statuses[1];
	return (statuses[1]);
}
