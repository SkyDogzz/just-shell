/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:13:08 by yandry            #+#    #+#             */
/*   Updated: 2025/04/21 19:33:20 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_builtins.h"
#include "ft_env.h"

static bool	is_builtin(const t_cmd *cmd)
{
	if (!cmd || !cmd->args)
		return (false);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		return (true);
	return (false);
}

static void	execute_builtin(t_cmd *cmd)
{
	ft_echo(cmd);
	exit(0);
}

static void	*copy_env_to_str(const void *env)
{
	char	*env_str;
	char	*str;

	str = ft_strjoin(((t_env *)env)->name, "=");
	env_str = ft_strjoin(str, ((t_env *)env)->value);
	free(str);
	return (env_str);
}

void	ft_execft(const char *path, char **args, t_list *env)
{
	if (execve(
		path,
		args,
		(char *const *)ft_lsttoarray_c(env, copy_env_to_str)) == -1)
	{
		ft_putstr_fd("ssh-xx: failed to run ", 2);
		ft_putendl_fd(args[0], 2);
		exit(127);
	}
}

void	ft_subprocess(t_cmd *cmd, t_list *env)
{
	char	*path;
	int		fd;
	char	*buffer;

	if (!cmd)
		exit(EXIT_FAILURE);
	if (is_builtin(cmd))
		execute_builtin((t_cmd *)cmd);
	path = ft_get_executable_path(cmd, env);
	if (!path)
	{
		ft_putstr_fd("ssh-xx: command not found ('", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd("')", 2);
		exit(127);
	}
	if (cmd->redir)
	{
		fd = open("./a", O_CREAT | O_WRONLY, 0644);
		while (cmd->redir)
		{
			if (((t_redir *)cmd->redir->content)->type != REDIR_INPUT &&
				((t_redir *)cmd->redir->content)->type != REDIR_HEREDOC)
			{
				cmd->redir = cmd->redir->next;
				continue ;
			}
			if (((t_redir *)cmd->redir->content)->type == REDIR_INPUT)
			{
				int fd2 = open(((t_redir *)cmd->redir->content)->file, O_RDONLY);
				printf("at start %d\n", fd);
				if (fd2 <= 0)
				{
					ft_putstr_fd("ssh-xx: can't open file ('", 1);
					ft_putstr_fd(((t_redir *)cmd->redir->content)->file, 1);
					ft_putendl_fd("')", 1);
					close(fd);
					exit(127);
				}
				buffer = ft_get_next_line(fd2);
				while(buffer)
				{
					buffer = ft_get_next_line(fd2);
					ft_putstr_fd(buffer, fd);
					free(buffer);
				}
				close(fd2);
			}
			else
			{
				ft_putstr_fd(((t_redir *)cmd->redir->content)->file, fd);
				ft_putstr_fd("\n", fd);
			}
			cmd->redir = cmd->redir->next;
		}
		close(fd);
		fd = open("./a", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink("./a");
	}
	ft_execft(path, cmd->args, env);
	exit(0);
}
