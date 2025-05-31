/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 11:19:34 by tstephan         ###   ########.fr       */
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

static int	exec_pipe_node(t_context *context, int fd_in)
{
	int		pipe_fds[2];
	pid_t	left_pid;

	if (setup_pipe(pipe_fds) == -1)
		return (-1);
	if (((t_leaf *)context->root->content)->type != NODE_PIPE)
	{
		ft_printf("Error: expected a pipe node, got %d\n",
			((t_leaf *)context->root->content)->type);
		return (-1);
	}
	if (context->root->left == NULL || context->root->right == NULL)
	{
		ft_printf("Error: pipe node has no left or right child\n");
		return (-1);
	}
	left_pid = exec_left_child(context->root->left, context, fd_in, pipe_fds);
	if (left_pid < 0)
		return (-1);
	if (fd_in != STDIN_FILENO)
		ft_close(&fd_in);
	ft_close(&pipe_fds[PIPE_RIGHT]);
	if (((t_leaf *)context->root->right->content)->type == NODE_WORD)
		return (handle_right_word_node(context,
				pipe_fds[PIPE_LEFT], left_pid));
	else
		return (handle_right_node(context, pipe_fds[PIPE_LEFT], left_pid));
}

int	ft_exec_pipeline(t_context * context)
{
	int						ret;
	t_context *new_context; 
	ret = 0;
	if (!context || !context->root)
		return (0);
	new_context = ft_get_execution_context(context->root->left, context->env);
	if (new_context
		&& ((t_leaf *)new_context->root->content)->type == NODE_PIPE)
		ft_exec_pipeline(new_context);
	ret = exec_pipe_node((t_context *)context, STDIN_FILENO);
	free((t_context *)new_context);
	return (ret);
}
