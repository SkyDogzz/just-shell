/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:13:08 by yandry            #+#    #+#             */
/*   Updated: 2025/04/17 16:58:20 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_builtins.h"
#include "includes/libft.h"

static bool	is_builtin(const t_cmd *cmd)
{
	if (!cmd || !cmd->args)
		return (false);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		return (true);
	return (false);
}

static void	execute_builtin(t_cmd *cmd)
{
	cmd->io[1] = STDOUT_FILENO;
	ft_echo(cmd);
	exit(0);
}

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
	if (execve(path, args, (char *const *)ft_lsttoarray_c(env, copy_env_to_str)) == -1)
	{
		ft_putstr_fd("ssh-xx: failed to run ", 2);
		ft_putendl_fd(args[0], 2);
		exit(127);
	}
}

void	ft_subprocess(const t_cmd *cmd, t_list *env)
{
	char	*path;

	if (!cmd)
		exit(EXIT_FAILURE);
	if (is_builtin(cmd))
		execute_builtin((t_cmd *)cmd);
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
