/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/04/08 11:59:14 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static char	*get_path(const t_cmd *cmd)
{
	const char	*fullpath;
	char	**splitted_paths;
	char	*base;
	char	*file;
	int		i;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	if (cmd->args[0][0] == '/')
		return (cmd->args[0]);
	fullpath = getenv("PATH");
	if (!fullpath)
		return (NULL);
	splitted_paths = ft_split(fullpath, ':');
	i = -1;
	while (splitted_paths[++i])
	{
		base = ft_strjoin(splitted_paths[i], "/");
		file = ft_strjoin(base, cmd->args[0]);
		free(base);
		if (access(file, F_OK | X_OK) == 0)
			return (file);
		free(file);
	}
	//file was either not found or does not have the right permissions. thats unfortunate
	i = 0;
	while (splitted_paths[i])
		free(splitted_paths[i++]);
	free(splitted_paths);
	return (NULL);
}

static void execute(const t_cmd *cmd, char *env[])
{
	char *executable = get_path(cmd);
	
	if (execve(executable, cmd->args,env) == -1)
	{
		ft_putstr_fd("Could not run ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		exit(1);
	}
}

static void	open_redirs(int in, int out, int redir_in, int redir_out)
{
	dup2(in, redir_in);
	dup2(out, redir_out);
}

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

static void	child(const t_btree *root, const int *pipe_fd, char **env)
{
	t_cmd	*cmd;
	if (!root)
		return ;
	cmd = ((t_leaf *)root->content)->cmd;
	open_redirs(cmd->io[0], pipe_fd[1], STDIN_FILENO, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(cmd, env);
	exit(0);
}

static void	middle_child(const t_btree *root, char **env)
{
	if (!root)
		return ;
	execute(((t_leaf *)root->content)->cmd, env);
	exit(0);
}

static int	exec_pipeline(const t_btree *root, char **env)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	size_t cmd_count = get_cmd_count(root);
	ft_printf("running %d commands\n", cmd_count);
	return (3);
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid[0] = fork();
	if (pid[0] == -1)
		exit(1);
	if (!pid[0])
		child(root->left, pipe_fd, env);
	close(pipe_fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		exit(1);
	if (!pid[0])
		child(root->right, pipe_fd, env);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

static int	exec_simple(const t_btree *root, char **env)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		middle_child(root, env);
	waitpid(pid, &status, 0);
	return (status);
}

int	ft_exec(t_btree	*root, char **env)
{
	int	ret;

	ret = 0;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = exec_simple(root, env);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = exec_pipeline(root, env);
	return (ret);
}
