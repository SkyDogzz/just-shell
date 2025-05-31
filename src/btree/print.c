/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:14:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/31 03:29:31 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*g_node_type[] = {
	"NODE_WORD",
	"NODE_REDIR",
	"NODE_PIPE",
	"NODE_LOGICAL"
};

static void	print_indent(int level, int is_last, int curr)
{
	if (curr >= level)
		return ;
	if (curr < level - 1)
		ft_printf("%s│   %s", CYAN, NC);
	else if (level > 0)
	{
		if (is_last)
			ft_printf("%s└── %s", CYAN, NC);
		else
			ft_printf("%s├── %s", CYAN, NC);
	}
	print_indent(level, is_last, curr + 1);
}

static void	print_args_line(t_btree *node, int level)
{
	t_leaf	*leaf;
	int		i;

	(void)level;
	if (!node || !node->content || ((t_leaf *)node->content)->type != NODE_WORD)
		return ;
	i = 0;
	leaf = node->content;
	if (!leaf->cmd->args[i])
		return ;
	ft_printf("[ ");
	while (leaf->cmd->args[i])
	{
		if (i > 0)
			ft_printf(", ");
		ft_printf("\"%s\"", leaf->cmd->args[i]);
		i++;
	}
	ft_printf(" ]\n");
}

static void	print_redir_line(const t_btree *node, int level)
{
	t_leaf	*leaf;
	t_list	*redirs;
	t_redir	*redir;	

	leaf = node->content;
	if (!leaf->cmd->redir)
		return ;
	redirs = leaf->cmd->redir;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (!redir)
			break ;
		print_indent(level, 0, 0);
		ft_printf("Redir file: %s\n", redir->file);
		print_indent(level, 0, 0);
		ft_printf("Redir type: %d\n", redir->type);
		redirs = redirs->next;
	}
}

static void	print_cmd_args(t_btree *node, int level)
{
	const t_leaf	*leaf;

	leaf = node->content;
	if (!leaf->cmd || leaf->type != NODE_WORD)
		return ;
	print_args_line(node, level + 1);
	print_redir_line(node, level + 1);
}

void	ft_print_tree(t_btree *root, int level, int is_last)
{
	t_leaf	*leaf;

	if (!root)
		return ;
	leaf = root->content;
	if (!leaf)
		return ;
	print_indent(level, is_last, 0);
	if (leaf->type == NODE_WORD)
		ft_printf("%s%s%s: ", PURPLE, g_node_type[leaf->type], NC);
	else
		ft_printf("%s%s%s\n", PURPLE, g_node_type[leaf->type], NC);
	print_cmd_args(root, level);
	if (root->left)
		ft_print_tree(root->left, level + 1, !root->right);
	if (root->right)
		ft_print_tree(root->right, level + 1, 1);
}
