/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:53:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/24 16:37:28 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_env.h"
#include <unistd.h>

static void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

static char	*find_exec_in_path(char *file, char **paths)
{
	char	*base;
	char	*full_path;
	int		i;

	i = -1;
	while (paths && paths[++i])
	{
		base = ft_strjoin(paths[i], "/");
		if (!base)
			continue ;
		full_path = ft_strjoin(base, file);
		free(base);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

static char	*find_exec_relative(char *file, t_list *env)
{
	t_env	*pwd;
	char	*rel_path;

	pwd = ft_get_env(env, "PWD");
	if (!pwd || !pwd->value)
		return (NULL);
	rel_path = ft_strjoin(pwd->value, &file[1]);
	if (rel_path && access(rel_path, F_OK | X_OK) == 0)
		return (rel_path);
	return (NULL);
}

char	*ft_get_executable_path(const t_cmd *cmd, t_list *env)
{
	char		**paths;
	char		*full_exec_path;
	t_env		*path_env;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	if (cmd->args[0][0] == '/')
		return (ft_strdup(cmd->args[0]));
	if (ft_strrchr(cmd->args[0], '/'))
	{
		full_exec_path = find_exec_relative(cmd->args[0], env);
		return (full_exec_path);
	}
	path_env = ft_get_env(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env->value, ':');
	full_exec_path = find_exec_in_path(cmd->args[0], paths);
	free_array(paths);
	return (full_exec_path);
}
