/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:13:08 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 18:35:02 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_execft(const char *path, char **args, char **env)
{
	if (execve(path, args, env) == -1)
	{
		ft_putstr_fd("ssh-xx: failed to run ", 2);
		ft_putendl_fd(args[0], 2);
		exit(127);
	}
}

void	ft_subprocess(const t_btree *root, char **env)
{
	char	*path;
	t_cmd	*cmd;

	if (!root || !root->content || !((t_leaf *)root->content)->cmd)
		return ;
	cmd = ((t_leaf *)root->content)->cmd;
	path = ft_get_executable_path(cmd);
	if (!path)
	{
		ft_putstr_fd("ssh-xx: command not found ('", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd("')", 2);
		exit(128);
	}
	ft_execft(path, cmd->args, env);
	exit(0);
}
