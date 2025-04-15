/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:12:04 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/26 16:33:48 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	ft_free_args(char **args)
{
	int	pos;

	pos = 0;
	while (args[pos])
	{
		free(args[pos]);
		pos++;
	}
	free(args);
}

void	ft_free_leaf(void *content)
{
	t_leaf	*leaf;

	if (!content)
		return ;
	leaf = (t_leaf *)content;
	if (leaf->cmd)
	{
		ft_free_args(leaf->cmd->args);
		free(leaf->cmd);
	}
	free(leaf);
	return ;
}
