/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/04/03 21:33:34 by Yanis Andry      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(const t_cmd *cmd)
{
	const char	*fullpath;
	char	**splitted_paths;
	char	*base;
	char	*file;
	int		i;
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

static void execute(const t_cmd *cmd)
{
	(void)cmd;
}

static void	child(const t_tree *root, const int *pipe_fd)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(root->cmd);
	exit(0);
}

static int	exec_pipeline(const t_tree *root)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid[0] = fork();
	if (pid[0] == -1)
		exit(1);
	if (!pid[0])
		child(root->left, pipe_fd);
	close(pipe_fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		exit(1);
	if (!pid[0])
		child(root->right, pipe_fd);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

int	ft_exec(t_tree	*root)
{
	if (!root)
		return (1);
	ft_putendl_fd(get_path(root->cmd), 1);
	return (exec_pipeline(root));
}
