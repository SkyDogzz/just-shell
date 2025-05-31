/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:19 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/31 05:21:28 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*https://unix.stackexchange.com/questions/442692/is-a-subshell*/

static void	ft_fuse_token(t_list **token)
{
	t_list	*act;
	t_list	*mem;
	t_token	*act_t;
	t_token	*next_t;

	act = *token;
	if (!act || !act->next)
		return ;
	act_t = act->content;
	next_t = act->next->content;
	act_t->content = ft_strjoin_free(act_t->content, next_t->content, BOTH);
	act_t->content = ft_strjoin_free(act_t->content, " ", FIRST);
	mem = act->next;
	act->next = act->next->next;
	ft_lstclear_t_token(mem);
}

static bool	ft_leveling(t_list *act, const t_token *act_t, int *level)
{
	if (!act->next)
		return (false);
	act_t = act->next->content;
	if (ft_strcmp(act_t->content, ")") == 0)
		(*level)--;
	else if (ft_strcmp(act_t->content, "(") == 0)
		(*level)++;
	else if (ft_strcmp(act_t->content, "$(") == 0)
		(*level)++;
	ft_fuse_token(&act);
	return (true);
}

static void	ft_group_subshell(t_list **token)
{
	t_list	*act;
	t_token	*act_t;
	int		level;

	level = 0;
	act = *token;
	while (act)
	{
		act_t = act->content;
		if (ft_strcmp(act_t->content, "$(") == 0
			|| ft_strcmp(act_t->content, "(") == 0)
		{
			level++;
			while (level)
				if (!ft_leveling(act, act_t, &level))
					break ;
		}
		act = act->next;
	}
}

static bool	ft_help(t_subshell *help)
{
	help->act_t = help->act->content;
	if (help->act_t->token_type == T_SUBSTITUTE)
	{
		if (ft_strcmp(help->act_t->content, "$(") == 0)
			help->level++;
		else if (ft_strcmp(help->act_t->content, "(") == 0)
			help->level++;
		else if (ft_strcmp(help->act_t->content, ")") == 0)
			help->level--;
	}
	if (help->level < 0)
		return (false);
	help->act = help->act->next;
	return (true);
}

bool	ft_findsubshell(t_list *env, t_list **token)
{
	t_subshell	help;

	help.act = *token;
	help.level = 0;
	while (help.act)
	{
		if (!ft_help(&help))
			return (false);
	}
	if (help.level != 0)
	{
		help.input = ft_read_subshell(help.level);
		help.pre = ft_doom_split(help.input);
		free(help.input);
		help.post = NULL;
		help.post = ft_string_to_token(env, help.post, help.pre);
		ft_lstadd_back(token, help.post);
		ft_lstclear(&help.pre, ft_lstclear_string);
	}
	ft_group_subshell(token);
	return (true);
}
