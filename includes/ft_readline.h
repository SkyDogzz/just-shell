/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:49:04 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 23:30:51 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include "../libft/includes/libft.h"

typedef struct s_readline
{
	char			*buffer;
	size_t			buffer_size;
	size_t			buffer_pos;
	char			c;
	struct termios	old_term;
}					t_readline;

char	*readline(const char *prompt);
char	*resize_buffer(t_readline *rl);
char	*finalize_input(t_readline *rl, int status);
int		setup_terminal(t_readline *rl);
int		init_readline(t_readline *rl, const char *prompt);
int		handle_special_chars(t_readline *rl);
int		process_input(t_readline *rl);
void	restore_terminal(t_readline *rl);
void	handle_backspace(t_readline *rl);

#endif
