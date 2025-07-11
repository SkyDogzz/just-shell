/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:05:51 by yandry            #+#    #+#             */
/*   Updated: 2025/07/11 19:48:50 by yandry           ###   ########.fr       */
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
	if (!args || !args[0])
		return ;
	if (!args[1])
	{
		home = ft_get_env(env, "HOME");
		if (!home || !home->value)
			return ;
		ft_strlcpy(path, home->value, PATH_MAX);
	}
	else if (ft_strncmp(args[1], "-", 1) == 0)
	{
		oldpwd = ft_get_env(env, "OLDPWD");
		if (!oldpwd || !oldpwd->value)
			return ;
		ft_strlcpy(path, oldpwd->value, PATH_MAX);
	}
	else
		ft_strlcpy(path, args[1], PATH_MAX);
}

int	ft_cd(const t_cmd *cmd, t_list **env)
{
	char	curr_dir[PATH_MAX];
	char	path[PATH_MAX];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		return (1);
	}
	if (!getcwd(curr_dir, sizeof curr_dir))
		*curr_dir = '\0';
	ft_memset(&path, '\0', PATH_MAX);
	get_newpath(*env, &path[0], cmd->args);
	if (chdir(path))
	{
		ft_dprintf(STDERR_FILENO,
			"cd: '%s' is not a directory\n", cmd->args[1]);
		return (1);
	}
	ft_update_env(env, "OLDPWD", curr_dir, true);
	getcwd(curr_dir, sizeof curr_dir);
	ft_update_env(env, "PWD", curr_dir, true);
	return (0);
}
