/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:31:11 by yandry            #+#    #+#             */
/*   Updated: 2025/04/23 13:46:38 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

int	ft_unset(const t_cmd *cmd, t_list *env)
{
	int	i;

	if (!cmd->args[1])
	{
		ft_dprintf(STDERR_FILENO, "unset: need at least 1 argument\n");
		return (1);
	}
	i = 1;
	while (cmd->args[i])
		ft_delete_env(&env, cmd->args[i++]);
	return (0);
}
