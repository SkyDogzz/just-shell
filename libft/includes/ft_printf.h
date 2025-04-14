/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:57:52 by yandry            #+#    #+#             */
/*   Updated: 2025/04/13 16:54:55 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdbool.h>

typedef void	(*t_out_func)(
						char character,
						void *buffer,
						size_t index,
						size_t n);
typedef struct s_printf
{
	char			*buffer;
	char			*format;
	size_t			max_len;
	t_out_func		out;
	va_list			va;
}					t_printf;

int	ft_vsnprintf(t_printf printf_args);

int	process_number(t_printf *args, size_t index);
int	process_char(t_printf *args, size_t index);
int	process_string(t_printf *args, size_t index, bool from_ptr);

int	process_pointer(t_printf *args, size_t index);
int	process_dec(t_printf *args, size_t index, bool unsig);
int	process_hex(t_printf *args, size_t index);

#endif
