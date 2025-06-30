/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:19:55 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/30 16:41:51 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

void	manage_redir(t_context *context, int fd[5], int *status)
{
	if (((t_leaf *)(context->context->content))->cmd->redir)
	{
		store_fd(fd);
		if (!open_outfile(((t_leaf *)(context->context->content))->cmd, fd))
		{
			restore_fd(fd);
			*status = 127 | CANT_OPEN_OUTFILE;
			return ;
		}
		if (!ft_infile_exec(((t_leaf *)(context->context)->content)->cmd))
		{
			restore_fd(fd);
			*status = 127 | CANT_OPEN_INFILE;
			return ;
		}
	}
	*status = 0;
}

static void	close_fds(int *fd, int number)
{
	while (number-- > 0)
		ft_close(&fd[number]);
}

static void	manage_fork(t_context *context, int fd[5], int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_set_sigaction_inter();
		close_fds(fd, 5);
		*status = ft_exec_global(((t_leaf *)(context->context->content))->cmd,
				context->env);
		ft_free_context(context, true);
		exit(*status);
	}
	else
		waitpid(pid, status, 0);
}

void	ft_exec_simple(t_context *context, int *status, bool first)
{
	int		fd[5];
	t_leaf	*leaf;

	leaf = context->context->content;
	if (!ft_cmd_exists(leaf->cmd, context->env))
	{
		*status = 127 | CMD_NOT_FOUND_FLAG;
		return ;
	}
	init_fds(fd);
	if (*status)
		return ;
	if (ft_is_builtin(leaf->cmd->args[0]) || first)
	{
		manage_redir(context, fd, status);
		if (*status)
			return ;
	}
	if (ft_is_builtin(leaf->cmd->args[0]))
		*status = ft_execute_builtin(leaf->cmd, &context->env);
	else
		manage_fork(context, fd, status);
	if (leaf->cmd->redir)
		restore_fd(fd);
}
