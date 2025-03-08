/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/03/01 15:48:30 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute(const t_cmd *cmd)
{
	(void)cmd;
}

static void	child(const t_tree *root, const int *pipe_fd)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(root->cmd);
	exit(0);
}

static int	exec_pipeline(const t_tree *root)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid[0] = fork();
	if (pid[0] == -1)
		exit(1);
	if (!pid[0])
		child(root->left, pipe_fd);
	close(pipe_fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		exit(1);
	if (!pid[0])
		child(root->right, pipe_fd);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

int	ft_exec(t_tree	*root)
{
	if (root->type == NODE_PIPE)
		return (exec_pipeline(root));
	exec_pipeline(root);
	return (238);
}
