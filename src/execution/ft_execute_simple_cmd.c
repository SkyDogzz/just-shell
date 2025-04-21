/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_simple_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/21 23:10:38 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

static int	show_command_not_found(const char *command)
{
	char	*error_message;
	int		alloc_len;

	alloc_len = ft_strlen(COMMAND_NOT_FOUND) + ft_strlen(command);
	error_message = ft_calloc(alloc_len, sizeof(char));
	if (!error_message)
		return (130 | CMD_NOT_FOUND_FLAG);
	ft_snprintf(error_message, alloc_len, COMMAND_NOT_FOUND, command);
	ft_putendl_fd(error_message, STDERR_FILENO);
	free(error_message);
	return (127 | CMD_NOT_FOUND_FLAG);
}

int	ft_exec_simple(const t_btree *root, t_list *env)
{
	int		pid;
	int		status;
	t_leaf	*leaf;
	char	*path;

	if (!root)
		return (0);
	leaf = (t_leaf *)root->content;
	if (ft_is_builtin(leaf->cmd->args[0]))
		return (ft_execute_builtin((t_cmd *)leaf->cmd, env));
	path = ft_get_executable_path(leaf->cmd, env);
	if (!path || access(path, X_OK) != 0)
		return (free(path), show_command_not_found(leaf->cmd->args[0]));
	free(path);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		ft_subprocess(leaf->cmd, env);
	waitpid(pid, &status, 0);
	return (status);
}
