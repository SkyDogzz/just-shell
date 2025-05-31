/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_tty_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:14:03 by yandry            #+#    #+#             */
/*   Updated: 2025/05/31 19:55:49 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_tty_shell(t_list *env)
{
	(void)env;
	ft_set_sigaction();
	ft_dprintf(STDERR_FILENO, "no.\n");
	return (-1);
}
