/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:26:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 06:36:25 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

static int	run_child(t_btree *root, t_list *env,
						int in_fd, int out_fd, int other_fd)
{
	pid_t		pid;
	int			status;
	t_context	*context;

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
	pid_t	pid;
	int		fd[2];

	if (!root)
		return (0);
	leaf = root->content;
	if (leaf->type != NODE_PIPE)
	{
		pid = run_child(root, env, in_fd, STDOUT_FILENO, -1);
		if (in_fd != STDIN_FILENO)
			ft_close(&in_fd);
		waitpid(pid, &status, 0);
		return (status);
	}
	if (pipev2(fd) == -1)
		return (127);
	pid = run_child(root->left, env, in_fd, fd[1], fd[0]);
	waitpid(pid, NULL, 0);
	ft_close(&fd[1]);
	if (in_fd != STDIN_FILENO)
		ft_close(&in_fd);
	status = launch_recursive(root->right, env, fd[0]);
	ft_close(&fd[0]);
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
