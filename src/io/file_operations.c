/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:47:20 by yandry            #+#    #+#             */
/*   Updated: 2025/05/16 13:32:57 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include <unistd.h>

bool	ft_close(int *fd)
{
	if (*fd < 0)
		return (false);
	if (close(*fd) == -1)
		return (false);
	*fd = -1;
	return (true);
}
