/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 04:33:23 by yandry            #+#    #+#             */
/*   Updated: 2025/06/19 06:10:28 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

static bool	cmd_is_alias(t_cmd *cmd)
{
	(void)cmd;
	return (false);
}

static bool	is_executable_file(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISREG(sb.st_mode) && access(path, X_OK) == 0)
		return (true);
	return (false);
}

static bool	cmd_is_builtin(t_cmd *cmd)
{
	return (cmd->args && ft_is_builtin(cmd->args[0]));
}

bool	cmd_exists_in_path(t_cmd *cmd, t_list *env)
{
	char	*path;

	path = ft_get_executable_path(cmd, env);
	if (!path)
		return (false);
	if (!is_executable_file(path))
	{
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

bool	ft_cmd_exists(t_cmd *cmd, t_list *env)
{
	bool	ret;

	if (!cmd)
		return (false);
	ret = (cmd_is_alias(cmd) || cmd_is_builtin(cmd)
			|| cmd_exists_in_path(cmd, env));
	if (!ret)
		ft_dprintf(STDERR_FILENO, "Command not found \"%s\"\n", cmd->args[0]);
	return (ret);
}
