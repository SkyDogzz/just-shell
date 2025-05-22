/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:25:13 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/17 15:54:02 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_leaf	*ft_create_leaf(t_node_type type, char	**args)
{
	t_leaf	*leaf;
	t_cmd	*cmd;

	leaf = (t_leaf *)malloc(sizeof(t_leaf));
	if (!leaf)
		return (NULL);
	leaf->type = type;
	leaf->cmd = NULL;
	if (args)
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (!cmd)
		{
			free(leaf);
			return (NULL);
		}
		cmd->args = args;
		cmd->redir = NULL;
		leaf->cmd = cmd;
	}
	return (leaf);
}
