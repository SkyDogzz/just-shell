/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:19:55 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 08:23:49 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

static int	manage_redir(t_contex2 *context, int fd[5], int *status)
{
	if (((t_leaf *)(context->context->content))->cmd->redir)
	{
		store_fd(fd);
		if (!open_outfile(((t_leaf *)(context->context->content))->cmd, fd))
		{
			ft_dprintf(STDERR_FILENO, "failed to open outfile\n");
			restore_fd(fd);
			*status = 127 | CANT_OPEN_OUTFILE;
			return (127);
		}
		if (!ft_infile_exec(((t_leaf *)(context->context)->content)->cmd))
		{
			ft_dprintf(STDERR_FILENO, "failed to open infile\n");
			restore_fd(fd);
			*status = 127 | CANT_OPEN_INFILE;
			return (127);
		}
	}
	return (0);
}

static void	close_fds(int *fd, int number)
{
	while (number-- > 0)
		ft_close(&fd[number]);
}

static void	manage_fork(t_contex2 *context, int fd[5], int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_set_sigaction_no_inter();
		close_fds(fd, 5);
		*status = ft_exec_global(((t_leaf *)(context->context->content))->cmd,
				context->env);
		ft_free_context(context, true);
		exit(*status);
	}
	else
		waitpid(pid, status, 0);
}

void	ft_exec_simple(t_contex2 *context, int *status)
{
	int		fd[5];

	if (!ft_cmd_exists(((t_leaf *)(context->context->content))->cmd, context->env))
	{
		*status = 127 | CMD_NOT_FOUND_FLAG;
		return ;
	}
	init_fds(fd);
	manage_redir(context, fd, status);
	if (*status)
		return ;
	if (ft_is_builtin(((t_leaf *)(context->context->content))->cmd->args[0]))
		*status = ft_execute_builtin(((t_leaf *)(context->context->content))->cmd,
				context->env);
	else
		manage_fork(context, fd, status);
	if (((t_leaf *)(context->context->content))->cmd->redir)
		restore_fd(fd);
}
