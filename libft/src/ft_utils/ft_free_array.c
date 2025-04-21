/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:18:29 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 21:18:51 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(void ***array)
{
	size_t	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
	*array = NULL;
}
