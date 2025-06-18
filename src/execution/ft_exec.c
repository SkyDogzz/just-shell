/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/06/18 13:45:49 by yandry           ###   ########.fr       */
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

int	ft_exec_global(t_cmd *cmd, t_list *env)
{
	char	*path;
	void	**env_arr;

	if (!ft_cmd_exists(cmd, env))
		return (127);
	if (ft_is_builtin(cmd->args[0]))
		return (ft_execute_builtin(cmd, env));
	path = ft_get_executable_path(cmd, env);
	if (!path)
		return (ft_freeplusplus(path, NULL));
	env_arr = ft_lsttoarray_c(env, copy_env_to_str);
	if (!execve(path, cmd->args, (char *const *)env_arr))
		return (ft_freeplusplus(path, &env_arr));
	return (0);
}

int	ft_exec(t_sombrax *context)
{
	t_btree	*root;
	int		status;

	dprintf(STDERR_FILENO, "*pom pom popm* j'execute depuis %d\n", getpid());
	if (!context)
		return (1);
	root = context->root;
	if (!root || !root->content)
		return (1);
	status = 0;
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ft_exec_simple(context, &status);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ft_exec_pipeline(context, &status);
	else if (((t_leaf *)root->content)->type == NODE_LOGICAL)
		ft_exec_logical(context, &status);
	return (status);
}
