/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:29 by yandry            #+#    #+#             */
/*   Updated: 2025/05/19 13:07:34 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

static bool	ft_fork(int fd[4], t_leaf *leaf, t_list *env, int *status)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		restore_fd(fd);
		return (false);
	}
	if (pid == 0)
		ft_subprocess(leaf->cmd, env);
	waitpid(pid, status, 0);
	return (true);
}

int	ft_exec_simple(const t_btree *root, t_list *env)
{
	int		status;
	t_leaf	*leaf;
	int		fd[4];
	bool	has_redir;

	status = 0;
	if (!root)
		return (0);
	leaf = (t_leaf *)root->content;
	if (!ft_cmd_exists(leaf->cmd, env))
		return (ft_show_error_message(COMMAND_NOT_FOUND, leaf->cmd->args[0],
				127, CMD_NOT_FOUND_FLAG));
	has_redir = leaf->cmd->redir != NULL;
	if (has_redir)
		store_fd(fd);
	if (!open_outfile((t_cmd *)leaf->cmd, fd))
		return (1);
	if (ft_is_builtin(leaf->cmd->args[0]))
	{
		status = ft_execute_builtin((t_cmd *)leaf->cmd, env);
		if (has_redir)
			restore_fd(fd);
		return (status);
	}
	if (!ft_fork(fd, leaf, env, &status))
		return (1);
	if (has_redir)
		restore_fd(fd);
	return (status);
}
