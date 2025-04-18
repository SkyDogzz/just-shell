/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline_recursive.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/18 18:53:49 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	execute_command(t_leaf *leaf, t_list *env)
{
	ft_subprocess(leaf->cmd, env);
	exit(EXIT_FAILURE);
}

static int	last_one(t_btree *node, t_list *env, int input_fd)
{
	int		pid;
	t_leaf	*leaf;

	pid = fork();
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		leaf = (t_leaf *)node->content;
		if (leaf->type == NODE_WORD)
			execute_command(leaf, env);
		else
			exit(ft_exec(node, env));
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, &g_exit, 0);
	return (g_exit);
}

static int	exec_left(int pipe_fds[2], int input_fd, t_btree *node, t_list *env)
{
	int		pid;
	t_leaf	*leaf;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_fds[0]);
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
		leaf = (t_leaf *)node->left->content;
		if (leaf->type == NODE_WORD)
			execute_command(leaf, env);
		else
			exit(ft_exec(node->left, env));
	}
	return (pid);
}

static int	exec_pipeline_recursive(t_btree *node, t_list *env, int input_fd)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (!node)
		return (EXIT_FAILURE);
	if (!node->right)
		return (last_one(node, env, input_fd));
	if (pipe(pipe_fds) == -1)
		return (EXIT_FAILURE);
	pid = exec_left(pipe_fds, input_fd, node, env);
	close(pipe_fds[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, NULL, 0);
	return (exec_pipeline_recursive(node->right, env, pipe_fds[0]));
}

int	ft_exec_pipeline(const t_btree *root, t_list *env)
{
	int	code;

	code = exec_pipeline_recursive((t_btree *)root, env, STDIN_FILENO);
	return (code);
}
