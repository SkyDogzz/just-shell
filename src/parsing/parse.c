/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:12:18 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 20:30:18 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char*g_node_type[] = {
	"NODE_WORD",
	"NODE_REDIR",
	"NODE_PIPE",
	"NODE_LOGICAL"
};

static void level_tabs(int level)
{
	int i;

	i = 0;
	while (i++ < level)
		ft_printf("\t");
}

static void print_cmd_args(t_tree *node, int level)
{
	int i;

	i = 0;
	while (node->cmd->args[i])
	{
		level_tabs(level);
		ft_printf("arg: %s\n", node->cmd->args[i++]);
	}
}

void ft_print_tree(t_tree *root, int level)
{
	if (!root)
		return ;
	level_tabs(level);
	ft_printf("type: %s\n", g_node_type[root->type]);
	if (root->cmd)
		print_cmd_args(root, level);
	if (root->left)
	{
		level_tabs(level);
		ft_printf("left:\n");
		ft_print_tree(root->left, level + 1);
	}
	if (root->right)
	{
		level_tabs(level);
		ft_printf("right:\n");
		ft_print_tree(root->right, level + 1);
	}
}

t_tree	*ft_parse(t_list *tokens)
{
	t_tree	*root;

	root = (t_tree *)malloc(sizeof(t_tree));
	root->type = 1;
	root->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	root->cmd->args = ft_split("here we are", ' ');
	root->left = NULL;
	root->right = NULL;	
	t_tree *right = (t_tree *)malloc(sizeof(t_tree));
	right->type = 1;
	right->cmd = NULL;
	right->left = NULL;
	right->right = NULL;
	root->right = right;
	ft_print_tree(root, 0);
	return (root);
	(void) tokens;
}
