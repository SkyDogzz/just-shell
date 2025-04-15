/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:53:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 18:46:39 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

char	*ft_get_executable_path(const t_cmd *cmd)
{
	char		**paths;
	char		*full_exec_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	if (cmd->args[0][0] == '/')
		return (ft_strdup(cmd->args[0]));
	if (!getenv("PATH"))
		return (NULL);
	paths = ft_split(getenv("PATH"), ':');
	full_exec_path = find_exec_in_path(cmd->args[0], paths);
	free_array(paths);
	return (full_exec_path);
}
