/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 04:33:23 by yandry            #+#    #+#             */
/*   Updated: 2025/05/09 13:12:45 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

static bool	cmd_is_alias(t_cmd *cmd)
{
	(void)cmd;
	return (false);
}

static bool	cmd_exists_in_path(t_cmd *cmd, t_list *env)
{
	char	*path;

	path = ft_get_executable_path(cmd, env);
	if (!path)
		return (false);
	free(path);
	return (true);
}

static bool	cmd_is_builtin(t_cmd *cmd)
{
	return (ft_is_builtin(cmd->args[0]));
}

bool	ft_cmd_exists(t_cmd *cmd, t_list *env)
{
	if (!cmd)
		return (false);
	return (cmd_is_alias(cmd)
		|| cmd_is_builtin(cmd)
		|| cmd_exists_in_path(cmd, env));
}
