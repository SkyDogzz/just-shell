/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:45:57 by yandry            #+#    #+#             */
/*   Updated: 2025/06/25 20:35:20 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H

# include "minishell.h"

# define COMMAND_NOT_FOUND "ssh-xx: command not found ('%s')\n"
# define COMMAND_FAILED "ssh-xx: failed to run command: %s\n"

# define MAX_PIDS_WAIT 65535

typedef enum e_pipeside
{
	PIPE_LEFT,
	PIPE_RIGHT
}		t_pipeside;

typedef enum e_pid_op
{
	OP_INSERT,
	OP_DELETE,
}		t_pid_op;

typedef struct s_context
{
	t_btree	*root;
	t_btree	*context;
	t_list	*env;
}	t_contex2;

t_contex2	*ft_get_execution_context(t_btree *tree, t_list *env);
void		ft_free_context(t_contex2 *context, bool clear_env);

int			ft_exec(t_contex2 *context, bool first);
int			ft_exec_global(t_cmd *cmd, t_list *env);

void		ft_exec_simple(t_contex2 *context, int *status, bool first);
int			ft_exec_logical(t_contex2 *context, int *status);
int			ft_exec_pipeline(t_contex2 *context, int *status);
int			run_child(t_contex2 *context, int in_fd, int out_fd, int other_fd);
int			manage_redir_child(t_contex2 *context);
int			launch_recursive(t_contex2 *context, int in_fd);
int			handle_pipe_node(t_contex2 *context, int in_fd);

bool		ft_is_builtin(const char *name);
bool		ft_cmd_exists(t_cmd *cmd, t_list *env);
int			ft_execute_builtin(const t_cmd *cmd, t_list *env);

char		*ft_get_executable_path(const t_cmd *cmd, t_list *env);

int			setup_pipe(int pipe_fds[2]);
void		destop_turbo(int pipe_fds[2]);

void		operate_on_pid_list(t_pid_op op, int pid);
void		wait_all(void);
t_contex2	*handle_input(char *input, t_list *env, int status);

#endif
