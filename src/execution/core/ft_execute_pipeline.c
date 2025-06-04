/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/06/03 13:36:49 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"
#include "ft_execution.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	ft_exec_with_redirects(t_cmd *cmd, t_list *env, int fd_in, int fd_out)
{
	int	ret;

	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		ft_close(&fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		ft_close(&fd_out);
	}
	if (ft_is_builtin(cmd->args[0]))
	{
		ret = ft_execute_builtin(cmd, env);
		return (ret);
	}
	ft_subprocess(cmd, env);
	exit(EXIT_FAILURE);
}

static int	execute_left_side(t_btree *left, t_context *context, int *pipe_fds)
{
	pid_t		pid;
	t_context	left_context;

	if (!pipe_fds || !context)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ft_close(&pipe_fds[0]);
		if (pipe_fds[1] >= 0 && dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			exit(1);
		ft_close(&pipe_fds[1]);
		if (context->fdin >= 0 && context->fdin != STDIN_FILENO)
		{
			if (dup2(context->fdin, STDIN_FILENO) == -1)
				exit(1);
			ft_close(&context->fdin);
		}
		left_context = *context;
		left_context.root = left;
		left_context.fdout = STDOUT_FILENO;
		exit(ft_exec(&left_context));
	}
	return (pid);
}

static int	execute_right_side(t_btree *right, t_context *context, int *pipe_fds)
{
	pid_t		pid;
	t_context	right_context;

	if (!pipe_fds || !context)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ft_close(&pipe_fds[1]);
		if (pipe_fds[0] >= 0 && dup2(pipe_fds[0], STDIN_FILENO) == -1)
			exit(1);
		ft_close(&pipe_fds[0]);
		right_context = *context;
		right_context.root = right;
		right_context.fdin = STDIN_FILENO;
		exit(ft_exec(&right_context));
	}
	return (pid);
}

static int	wait_all(pid_t left, pid_t right)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	waitpid(left, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	waitpid(right, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}

int	ft_exec_pipeline(t_context *context)
{
	int		pipe_fds[2];
	pid_t	left_pid;
	pid_t	right_pid;
	t_btree	*root;

	if (!context || !context->root)
		return (1);
	root = context->root;
	if (setup_pipe(pipe_fds) == -1)
		return (-1);
	if (((t_leaf *)root->content)->type != NODE_PIPE)
	{
		ft_printf("Error: expected a pipe node, got %d\n",
			((t_leaf *)root->content)->type);
		destop_turbo(pipe_fds);
		return (-1);
	}
	if (root->left == NULL || root->right == NULL)
	{
		ft_printf("Error: pipe node has no left or right child\n");
		destop_turbo(pipe_fds);
		return (-1);
	}
	left_pid = execute_left_side(root->left, context, pipe_fds);
	right_pid = execute_right_side(root->right, context, pipe_fds);
	destop_turbo(pipe_fds);
	if (left_pid == -1 || right_pid == -1)
		return (-1);
	return (wait_all(left_pid, right_pid));
}

