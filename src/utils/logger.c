/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:33:53 by yandry            #+#    #+#             */
/*   Updated: 2025/05/09 22:43:17 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_show_error_message(const char *message_format, const char *context,
					int exit_code, int flag)
{
	char	*error_message;
	size_t	alloc_len;

	alloc_len = ft_strlen(message_format) + ft_strlen(context);
	error_message = ft_calloc(alloc_len, sizeof(char));
	if (!error_message)
		return (exit_code | flag);
	ft_snprintf(error_message, alloc_len, message_format, context);
	ft_putendl_fd(error_message, STDERR_FILENO);
	free(error_message);
	return (exit_code | flag);
}
