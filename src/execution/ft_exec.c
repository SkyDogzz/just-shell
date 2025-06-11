/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/06/11 15:54:52 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "minishell.h"
#include <unistd.h>

static int	ft_freeplusplus(char *path, void ***env_arr)
{
	if (path)
		free(path);
	if (env_arr)
		ft_free_array(env_arr);
	return (127);
}

static int	ft_sombrax(t_cmd *cmd, t_list *env)
{
	char	*path;
	void	**env_arr;

	if (!ft_cmd_exists(cmd, env))
		return (127);
	if (ft_is_builtin(cmd->args[0]))
		return (ft_execute_builtin(cmd, env));
	path = ft_get_executable_path(cmd, env);
	if (!path)
		return ft_freeplusplus(path, NULL);
	env_arr = ft_lsttoarray_c(env, copy_env_to_str);
	if (!env_arr)
		return ft_freeplusplus(path, NULL);
	if (!execve(path, cmd->args, (char * const *)env_arr))
		return ft_freeplusplus(path, &env_arr);
	return (0);
}

static void init_fds(int fd[4])
{
	fd[0] = -2;
	fd[1] = -2;
	fd[2] = -2;
	fd[3] = -2;
}

static int	ft_exec_simple(t_context *context, int *status)
{
	pid_t	pid;
	int		ret;
	int		fd[4];

	ret = 0;
	init_fds(fd);
	if (((t_leaf *)(context->root->content))->cmd->redir)
	{
		store_fd(fd);
		if (!open_outfile(((t_leaf *)(context->root->content))->cmd, fd))
		{
			fprintf(stdout, "failed to open outfile\n");
			restore_fd(fd);
			return (127);
		}
		if (!ft_infile_exec(((t_leaf *)(context->root)->content)->cmd))
		{
			fprintf(stdout, "failed to open outfile\n");
			restore_fd(fd);
			return (127);
		}
	}
	pid = fork();
	if (pid == 0)
		ret = ft_sombrax(((t_leaf *)(context->root->content))->cmd, context->env);
	waitpid(pid, status, 0);
	if (((t_leaf *)(context->root->content))->cmd->redir)
		restore_fd(fd);
	return (ret);
}

static int	ft_exec_pipeline(t_context *context)
{
	printf("Exec pipeline\n");
	return (0);
	(void) context;
}

static int	ft_exec_logical(t_context *context)
{
	printf("Exec logical\n");
	return (0);
	(void) context;
}

int	ft_exec(t_context *context)
{
	int		ret;
	t_btree	*root;
	int		status;

	if (!context)
		return (1);
	ret = 0;
	root = context->root;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = ft_exec_simple(context, &status);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = ft_exec_pipeline(context);
	else if (((t_leaf *)root->content)->type == NODE_LOGICAL)
		ret = ft_exec_logical(context);
	return (ret);
}
