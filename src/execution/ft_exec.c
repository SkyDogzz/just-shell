/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/04/14 03:33:35 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

/*static void	open_redirs(int in, int out, int redir_in, int redir_out)
{
	dup2(in, redir_in);
	dup2(out, redir_out);
}*/

/*static size_t	get_cmd_count(const t_btree *root)
{
	size_t	count;

	count = 0;
	if (!root)
		return (count);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		count++;
	count += get_cmd_count(root->left);
	count += get_cmd_count(root->right);
	return (count);
}*/

// 💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀
static int	exec_pipeline_r(const t_btree *node, char **env)
{
	t_leaf	*leaf;
	int		pipe_fds[2];
	pid_t	pids[2];
	int		statuses[2];

	if (!node)
		return (0);
	leaf = (t_leaf *)node->content;
	if (leaf->type == NODE_PIPE)
	{
		if (pipe(pipe_fds) == -1)
			return (-1);
		pids[0] = fork();
		if (pids[0] == -1)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			return (-1);
		}
		if (pids[0] == 0)
		{
			close(pipe_fds[0]);
			if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			{
				close(pipe_fds[1]);
				exit(EXIT_FAILURE);
			}
			close(pipe_fds[1]);
			if (node->left)
			{
				if (((t_leaf *)node->left->content)->type == NODE_WORD)
					ft_subprocess(((t_leaf *)node->left->content)->cmd, env);
				else
					exit(exec_pipeline_r(node->left, env));
			}
			exit(EXIT_FAILURE);
		}
		pids[1] = fork();
		if (pids[1] == -1)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			kill(pids[0], SIGTERM);
			waitpid(pids[0], NULL, 0);
			return (-1);
		}
		if (pids[1] == 0)
		{
			close(pipe_fds[1]);
			if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
			{
				close(pipe_fds[0]);
				exit(EXIT_FAILURE);
			}
			close(pipe_fds[0]);
			if (node->right)
			{
				if (((t_leaf *)node->right->content)->type == NODE_WORD)
					ft_subprocess(((t_leaf *)node->right->content)->cmd, env);
				else
					exit(exec_pipeline_r(node->right, env));
			}
			exit(EXIT_FAILURE);
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		waitpid(pids[0], &statuses[0], 0);
		waitpid(pids[1], &statuses[1], 0);
		return (statuses[1]);
	}
	else if (leaf->type == NODE_WORD)
	{
		pids[0] = fork();
		if (pids[0] == -1)
			return (-1);
		if (pids[0] == 0)
		{
			ft_subprocess(leaf->cmd, env);
			exit(EXIT_FAILURE);
		}
		waitpid(pids[0], &statuses[0], 0);
		return (statuses[0]);
	}
	return (-1);
}

static int	exec_pipeline(const t_btree *root, char **env)
{
	int		status;
	pid_t	pid;
	t_leaf	*leaf;

	if (!root)
		return (0);
	leaf = (t_leaf *)root->content;
	if (!root->left && !root->right && leaf->type == NODE_WORD)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			ft_subprocess(leaf->cmd, env);
		waitpid(pid, &status, 0);
		return (status);
	}
	return (exec_pipeline_r(root, env));
}

int	ft_exec(t_btree	*root, char **env)
{
	int	ret;

	ret = 0;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = ft_exec_simple(root, env);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = exec_pipeline(root, env);
	return (ret);
}
