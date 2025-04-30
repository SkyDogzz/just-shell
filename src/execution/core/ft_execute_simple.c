/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/30 18:31:26 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include <stdlib.h>

static int	show_command_not_found(const char *command)
{
	char	*error_message;
	int		alloc_len;

	alloc_len = ft_strlen(COMMAND_NOT_FOUND) + ft_strlen(command);
	error_message = ft_calloc(alloc_len, sizeof(char));
	if (!error_message)
		return (127 | CMD_NOT_FOUND_FLAG);
	ft_snprintf(error_message, alloc_len, COMMAND_NOT_FOUND, command);
	ft_putendl_fd(error_message, STDERR_FILENO);
	free(error_message);
	return (127 | CMD_NOT_FOUND_FLAG);
}

static int	test_path(t_leaf *leaf, t_list *env, int fd[4])
{
	char	*path;
	int		ret;

	path = ft_get_executable_path(leaf->cmd, env);
	if (!path || access(path, X_OK) != 0)
	{
		free(path);
		ret = show_command_not_found(leaf->cmd->args[0]);
		restore_fd(fd);
		return (ret);
	}
	free(path);
	return (0);
}

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

	if (!root)
		return (0);
	leaf = (t_leaf *)root->content;
	store_fd(fd);
	if (!open_outfile((t_cmd *)leaf->cmd, fd))
		return (1);
	if (ft_is_builtin(leaf->cmd->args[0]))
		return (ft_execute_builtin((t_cmd *)leaf->cmd, env));
	status = test_path(leaf, env, fd);
	if (status != 0)
		return (status);
	if (!ft_fork(fd, leaf, env, &status))
		return (1);
	restore_fd(fd);
	return (status);
}
