/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:25:13 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/06 16:25:24 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_leaf	*ft_create_leaf(t_node_type type, char	**args)
{
	t_leaf	*leaf;

	leaf = (t_leaf *)malloc(sizeof(t_leaf));
	leaf->type = type;
	leaf->cmd = NULL;
	if (args)
	{
		leaf->cmd = (t_cmd *)malloc(sizeof(t_cmd));
		leaf->cmd->args = args;
	}
	return (leaf);
}
