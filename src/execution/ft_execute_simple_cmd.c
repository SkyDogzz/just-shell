/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_simple_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/14 03:01:32 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exec_simple(const t_btree *root, char **env)
{
	int		pid;
	int		status;
	t_leaf	*leaf;

	if (!root)
		return (0);
	leaf = (t_leaf *)root->content;
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		ft_subprocess(leaf->cmd, env);
	waitpid(pid, &status, 0);
	return (status);
}
