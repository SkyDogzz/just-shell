/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:50:50 by yandry            #+#    #+#             */
/*   Updated: 2025/06/30 15:12:39 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

static void	skip_flags(int *index, bool *newline, char **argh)
{
	int	j;

	while (argh[*index] && argh[*index][0] == '-')
	{
		j = 1;
		while (argh[*index][j] == 'n')
			j++;
		if (!(*index)[argh][j])
			*newline = ((*index)++, false);
		else
			break ;
	}
}

int	ft_echo(const t_cmd *cmd, t_list **env)
{
	bool	has_newline;
	int		i;

	(void)*env;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	has_newline = true;
	i = 1;
	skip_flags(&i, &has_newline, cmd->args);
	if (cmd->args[i])
		ft_putstr_fd(cmd->args[i++], STDOUT_FILENO);
	while (i[cmd->args])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(cmd->args[i++], STDOUT_FILENO);
	}
	if (has_newline)
		ft_putendl_fd("", STDOUT_FILENO);
	return (0);
}
