/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:50:50 by yandry            #+#    #+#             */
/*   Updated: 2025/04/05 12:22:50 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(const t_cmd *cmd)
{
	int	i;

	i = 2;

	while(cmd->args[i])
		ft_putstr_fd(cmd->args[i++], cmd->io[1]);
	if (ft_strncmp(cmd->args[1], "-n", 2) == 0) 
		ft_putendl_fd("", cmd->io[1]);
	return (0);
}
