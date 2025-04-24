/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:19:17 by yandry            #+#    #+#             */
/*   Updated: 2025/04/24 19:01:28 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "ft_builtins.h"

static const t_builtin	*get_builtin(const char *name)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strncmp(g_builtins[i].name, name, ft_strlen(name)) == 0)
			return (&g_builtins[i]);
		i++;
	}
	return (NULL);
}

int	ft_execute_builtin(const t_cmd *cmd, t_list *env)
{
	const t_builtin	*builtin;
	int				ret;
	int				fd[2];

	builtin = get_builtin(cmd->args[0]);
	if (!builtin)
		return (1);
	store_fd(fd);
	fd[1] = open_outfile((t_cmd *)cmd);
	if (fd[1] == 0)
	{
		ft_dprintf(STDERR_FILENO, "ssh-xx: %s ('%s')\n",
			strerror(errno), ((t_redir *)cmd->redir->content)->file);
		restore_fd(fd);
		return (1);
	}
	ret = builtin->func(cmd, env);
	restore_fd(fd);
	return (ret);
}
