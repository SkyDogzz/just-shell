/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/04/12 18:31:00 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include <unistd.h>

/*static void	open_redirs(int in, int out, int redir_in, int redir_out)
{
	dup2(in, redir_in);
	dup2(out, redir_out);
}*/

static size_t	get_cmd_count(const t_btree *root)
{
	size_t	count;

	count = 0;
	if (!root)
		return (count);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		count++;
	count += get_cmd_count(root->left);
	count += get_cmd_count(root->right);
	return (count);
}

static int	exec_pipeline(const t_btree *root, char **env)
{
	int		pipe_fd[2];
	pid_t	pid[2];
	size_t	cmd_count;

	cmd_count = get_cmd_count(root);
	ft_printf("running %d commands\n", cmd_count);
	return (3);
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid[0] = fork();
	if (pid[0] == -1)
		exit(1);
	if (!pid[0])
		ft_subprocess(root->left, env);
	close(pipe_fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		exit(1);
	if (!pid[0])
		ft_subprocess(root->right, env);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

int	ft_exec(t_btree	*root, char **env)
{
	int	ret;

	ret = 0;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = ft_exec_simple(root, env);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = exec_pipeline(root, env);
	return (ret);
}
