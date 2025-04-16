/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:50:50 by yandry            #+#    #+#             */
/*   Updated: 2025/04/16 18:34:00 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "includes/libft.h"

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

// TODO: echo
void	ft_echo(const t_cmd *cmd)
{
	bool	has_newline;
	int		i;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	has_newline = true;
	i = 1;
	skip_flags(&i, &has_newline, cmd->args);
	if (cmd->args[i])
		ft_putstr_fd(cmd->args[i++], cmd->io[1]);
	while (i[cmd->args])
	{
		ft_putstr_fd(" ", cmd->io[1]);
		ft_putstr_fd(cmd->args[i++], cmd->io[1]);
	}
	if (has_newline)
		ft_putendl_fd("", cmd->io[1]);
}
