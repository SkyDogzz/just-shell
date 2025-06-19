/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:48:08 by yandry            #+#    #+#             */
/*   Updated: 2025/06/19 12:39:00 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

# include <stdbool.h>
# include "minishell.h"

bool	ft_close(int *fd);
void	init_fds(int fd[5]);
int		dup2v2(int fd, int fd2);
int		pipev2(int *pipedes);
bool	ft_redir_all(t_cmd *cmd, int fd, char *filename);

#endif
