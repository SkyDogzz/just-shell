/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:12:04 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/23 09:23:35 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	del(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	if (!redir)
		return ;
	if (!redir->file)
	{
		free(redir);
		return ;
	}
	free(redir->file);
	free(redir);
}

void	ft_free_leaf(void *content)
{
	t_leaf	*leaf;

	if (!content)
		return ;
	leaf = (t_leaf *)content;
	if (leaf->cmd)
	{
		ft_lstclear(&leaf->cmd->redir, del);
		ft_free_args(leaf->cmd->args);
		free(leaf->cmd);
	}
	free(leaf);
	return ;
}
