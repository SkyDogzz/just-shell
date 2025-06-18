/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:26:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/18 16:49:33 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

static int	run_child(t_sombrax *context, int in_fd, int out_fd)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (127);
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
			dup2(in_fd, STDIN_FILENO);
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		status = ft_exec(context);
		ft_free_context(context, true);
		exit(status);
	}
	return (pid);
}

static int	launch_recursive(t_sombrax *context, int in_fd)
{
	int		status;
	t_leaf	*leaf;
	pid_t	pid[2];
	int		fd[2];
	t_sombrax	contexts[2];

	if (!context || !context->root)
		return (0);
	leaf = context->root->content;
	if (leaf->type != NODE_PIPE)
	{
		pid[0] = run_child(context, in_fd, STDOUT_FILENO);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		waitpid(pid[0], &status, 0);
		return (status);
	}
	if (pipe(fd) == -1)
		return (127);
	ft_memset(&contexts[0], 0, sizeof(t_sombrax));
	ft_memset(&contexts[1], 0, sizeof(t_sombrax));
	contexts[0].env = context->env;
	contexts[0].root = context->root->left;
	pid[1] = run_child(&contexts[0], in_fd, fd[1]);
	close(fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	contexts[1].env = context->env;
	contexts[1].root = context->root->right;
	status = launch_recursive(&contexts[1], fd[0]);
	waitpid(pid[1], NULL, 0);
	return (status);
}

int	ft_exec_pipeline(t_sombrax *context, int *status)
{
	if (!context || !context->root)
		return (0);
	if (((t_leaf *)context->root->content)->type == NODE_PIPE)
		*status = launch_recursive(context, STDIN_FILENO);
	return (*status);
}
