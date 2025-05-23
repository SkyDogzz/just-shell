/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:45:57 by yandry            #+#    #+#             */
/*   Updated: 2025/04/26 18:48:04 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H

# include "minishell.h"

# define COMMAND_NOT_FOUND "ssh-xx: command not found ('%s')\n"
# define COMMAND_FAILED "ssh-xx: failed to run command: %s\n"

typedef enum e_pipeside
{
	PIPE_LEFT,
	PIPE_RIGHT
}		t_pipeside;

typedef struct s_context
{
	t_btree	*root;
	t_list	*env;
}	t_context;

t_context	*ft_get_execution_context(t_btree *tree, t_list *env);

int			ft_exec(t_context *context);

bool		ft_is_builtin(const char *name);
int			ft_execute_builtin(const t_cmd *cmd, t_list *env);

int			ft_exec_simple(const t_btree *root, t_list *env);
int			ft_exec_pipeline(const t_btree *root, t_list *env, int fd_in);
int			ft_exec_logical(const t_btree *root, t_list *env);
int			ft_exec_with_redirects(t_cmd *cmd,
				t_list *env,
				int fd_in,
				int fd_out);

void		ft_subprocess(t_cmd *cmd, t_list *env);
void		ft_execft(const char *path, char *args[], t_list *env);
char		*ft_get_executable_path(const t_cmd *cmd, t_list *env);

int			setup_pipe(int pipe_fds[2]);
void		destop_turbo(int pipe_fds[2]);

int			exec_left_child(t_btree *node, t_list *env,
				int fd_in, int pipe_fds[2]);
int			handle_right_word_node(t_btree *node, t_list *env, int pipe_fd,
				pid_t left_pid);
int			handle_right_node(t_btree *node, t_list *env, int pipe_fd,
				pid_t left_pid);
#endif
