/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:13:08 by yandry            #+#    #+#             */
/*   Updated: 2025/04/22 17:14:46 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_env.h"

static void	*copy_env_to_str(const void *env)
{
	char	*env_str;
	char	*str;

	str = ft_strjoin(((t_env *)env)->name, "=");
	env_str = ft_strjoin(str, ((t_env *)env)->value);
	free(str);
	return (env_str);
}

void	ft_execft(const char *path, char **args, t_list *env)
{
	if (execve(path, args,
			(char *const *)ft_lsttoarray_c(env, copy_env_to_str)) == -1)
	{
		ft_dprintf(STDERR_FILENO, COMMAND_FAILED, args[0]);
		exit(127);
	}
}

void	ft_subprocess(t_cmd *cmd, t_list *env)
{
	char	*path;

	if (!cmd)
		exit(EXIT_FAILURE);
	path = ft_get_executable_path(cmd, env);
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, COMMAND_NOT_FOUND, cmd->args[0]);
		exit(128);
	}
	ft_infile_exec(cmd);
	ft_execft(path, cmd->args, env);
	exit(0);
}
