/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/04/23 15:52:26 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "minishell.h"

int	ft_exit(const t_cmd *cmd, t_list *env)
{
	(void)env;
	if (cmd->args[1])
		g_exit = ft_atoi(cmd->args[1]) << 8;
	return (238);
}
