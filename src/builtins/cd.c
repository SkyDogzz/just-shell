/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:05:51 by yandry            #+#    #+#             */
/*   Updated: 2025/04/21 18:26:39 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include <linux/limits.h>
#include <unistd.h>

static void	get_newpath(t_list *env, char *path, char **args)
{
	t_env	*home;
	t_env	*oldpwd;

	*path = '\0';
	home = ft_get_env(env, "HOME");
	if (!home || !home->value)
		return ;
	oldpwd = ft_get_env(env, "OLDPWD");
	if (!oldpwd || !oldpwd->value)
		return ;
	if (args && args[0] && !args[1])
		ft_memcpy(path, home->value, PATH_MAX);
	else if (ft_strncmp(args[1], "-", 1) == 0)
		ft_memcpy(path, oldpwd->value, PATH_MAX);
	else
		ft_memcpy(path, args[1], PATH_MAX);
}

int	ft_cd(const t_cmd *cmd, t_list *env)
{
	char	curr_dir[PATH_MAX];
	char	path[PATH_MAX];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (!getcwd(curr_dir, sizeof curr_dir))
		*curr_dir = '\0';
	get_newpath(env, &path[0], cmd->args);
	if (chdir(path))
	{
		ft_putstr_fd("cd: not a directory: ", STDERR_FILENO);
		ft_putendl_fd(cmd->args[1], STDERR_FILENO);
		return (1);
	}
	ft_update_env(&env, "OLDPWD", curr_dir);
	return (0);
}
