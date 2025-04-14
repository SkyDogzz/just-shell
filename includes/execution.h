/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:45:57 by yandry            #+#    #+#             */
/*   Updated: 2025/04/14 17:12:02 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int		ft_exec_simple(const t_btree *root, char **env);
int		ft_exec_pipeline(const t_btree *root, char **env);

void	ft_subprocess(const t_cmd *cmd, char **env);
void	ft_execft(const char *path, char *args[], char *env[]);
char	*ft_get_executable_path(const t_cmd *cmd);

int		setup_pipe(int pipe_fds[2]);
void	cleanup_pipe(int pipe_fds[2]);
#endif
