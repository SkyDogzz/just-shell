/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/06/22 16:01:48 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "minishell.h"

int	ft_exit(const t_cmd *cmd, t_list *env)
{
	int		exit_code;
	t_env	*last_status;

	(void)env;
	if (cmd->args[1])
		exit_code = ft_atoi(cmd->args[1]) & 0xFF;
	else
	{
		last_status = ft_get_env(env, "?");
		if (last_status && last_status->value)
			exit_code = ft_atoi(last_status->value) & 0xFF;
		else
			exit_code = 0;
	}
	return (exit_code | EXIT_SHELL);
}
