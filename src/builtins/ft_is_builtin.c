/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:13:04 by yandry            #+#    #+#             */
/*   Updated: 2025/04/24 21:59:40 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_builtins.h"

bool	ft_is_builtin(const char *name)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(g_builtins[i].name, name) == 0)
			return (true);
		i++;
	}
	return (false);
}
