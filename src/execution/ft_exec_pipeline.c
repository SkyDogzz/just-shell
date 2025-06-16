/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:26:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/16 20:09:24 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

static int	run_child(t_btree *root, t_list *env, int in_fd, int out_fd)
{
	pid_t		pid;
	int			status;
	t_context	*context;

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
		context = ft_get_execution_context(root, env);
		status = ft_exec(context);
		ft_free_context(context, false);
		exit(status);
	}
	return (pid);
}

static int	launch_recursive(t_btree *root, t_list *env, int in_fd)
{
	int		status;
	t_leaf	*leaf;
	pid_t	pid[2];
	int		fd[2];

	if (!root)
		return (0);
	leaf = root->content;
	if (leaf->type != NODE_PIPE)
	{
		pid[0] = run_child(root, env, in_fd, STDOUT_FILENO);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		waitpid(pid[0], &status, 0);
		return (status);
	}
	if (pipe(fd) == -1)
		return (127);
	pid[1] = run_child(root->left, env, in_fd, fd[1]);
	close(fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	status = launch_recursive(root->right, env, fd[0]);
	waitpid(pid[1], NULL, 0);
	return (status);
}

int	ft_exec_pipeline(t_context *context, int *status)
{
	if (!context || !context->root)
		return (0);
	if (((t_leaf *)context->root->content)->type == NODE_PIPE)
		*status = launch_recursive(context->root, context->env, STDIN_FILENO);
	return (*status);
}
