/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:13:08 by yandry            #+#    #+#             */
/*   Updated: 2025/04/30 18:15:15 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_env.h"

void	ft_execft(const char *path, char **args, t_list *env)
{
	t_list		*exported_env;
	char *const	*env_arr;

	exported_env = ft_lstcpy_if(env, is_env_exported, clear_env);
	env_arr = (char *const *)ft_lsttoarray_c(exported_env, copy_env_to_str);
	ft_lstclear(&exported_env, clear_env);
	if (execve(path, args, env_arr) == -1)
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
