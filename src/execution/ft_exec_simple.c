/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:19:55 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/12 15:35:52 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_execution.h"
#include "ft_io.h"

int	ft_exec_simple(t_context *context, int *status)
{
	pid_t	pid;
	int		ret;
	int		fd[5];

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
	{
		ft_close(&fd[0]);
		ft_close(&fd[1]);
		ft_close(&fd[2]);
		ft_close(&fd[3]);
		ft_close(&fd[4]);
		ret = ft_exec_global(((t_leaf *)(context->root->content))->cmd, context->env);
		exit(ret);
	}
	else
		waitpid(pid, status, 0);
	if (((t_leaf *)(context->root->content))->cmd->redir)
		restore_fd(fd);
	return (ret);
}
