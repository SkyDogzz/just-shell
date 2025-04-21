/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:15:59 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 22:31:55 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"
#include "minishell.h"
#include <unistd.h>

/*static void	open_redirs(int in, int out, int redir_in, int redir_out)
{
	dup2(in, redir_in);
	dup2(out, redir_out);
}*/

/*static size_t	get_cmd_count(const t_btree *root)
{
	size_t	count;

	count = 0;
	if (!root)
		return (count);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		count++;
	count += get_cmd_count(root->left);
	count += get_cmd_count(root->right);
	return (count);
}*/

// 💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀
int	ft_exec(t_btree	*root, t_list *env)
{
	int	ret;

	ret = 0;
	if (!root || !root->content)
		return (1);
	if (((t_leaf *)root->content)->type == NODE_WORD)
		ret = ft_exec_simple(root, env);
	else if (((t_leaf *)root->content)->type == NODE_PIPE)
		ret = ft_exec_pipeline(root, env, STDIN_FILENO);
	return (ret);
}
