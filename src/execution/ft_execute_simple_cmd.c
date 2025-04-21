/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_simple_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/21 16:11:11 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_env.h"

int	ft_exec_simple(const t_btree *root, t_list *env)
{
	int		pid;
	int		status;
	t_leaf	*leaf;
	char	*path;

	if (!root)
		return (0);
	leaf = (t_leaf *)root->content;
	path = ft_get_executable_path(leaf->cmd, env);
	if (!path || access(path, X_OK) != 0)
	{
		ft_putstr_fd("ssh-xx: command not found ('", 2);
		ft_putstr_fd(leaf->cmd->args[0], 2);
		ft_putendl_fd("')", 2);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		ft_subprocess(leaf->cmd, env);
	waitpid(pid, &status, 0);
	g_exit = status;
	return (status);
}
