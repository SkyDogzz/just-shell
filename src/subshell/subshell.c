/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:19 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/18 14:31:51 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (ft_strncmp(act_t->content, "$(",
				ft_getmax(ft_strlen(act_t->content), 2)) == 0)
		{
			level++;
			while (level)
			{
				if (!act->next)
					break ;
				act_t = act->next->content;
				if (ft_strncmp(act_t->content, ")",
						ft_getmax(ft_strlen(act_t->content), 1)) == 0)
					level--;
				else if (ft_strncmp(act_t->content, "$(",
						ft_getmax(ft_strlen(act_t->content), 2)) == 0)
					level++;
				ft_fuse_token(&act);
			}
		}
		act = act->next;
	}
}

bool	ft_findsubshell(t_list **token)
{
	t_list	*act;
	t_token	*act_t;
	int		level;
	t_list	*pre;
	t_list	*post;
	char	*input;

	act = *token;
	level = 0;
	while (act)
	{
		act_t = act->content;
		if (act_t->token_type == T_SUBSTITUTE)
		{
			if (ft_strncmp(act_t->content, "$(",
					ft_getmax(ft_strlen(act_t->content), 2)) == 0)
				level++;
			if (ft_strncmp(act_t->content, ")",
					ft_getmax(ft_strlen(act_t->content), 1)) == 0)
				level--;
		}
		if (level < 0)
			return (false);
		act = act->next;
	}
	if (level != 0)
	{
		input = ft_read_subshell(level);
		pre = ft_doom_split(input);
		free(input);
		post = NULL;
		post = ft_string_to_token(post, pre);
		ft_lstadd_back(token, post);
		ft_lstclear(&pre, ft_lstclear_string);
	}
	ft_lstprint_tokens(*token, "Print pre subshell");
	ft_group_subshell(token);
	ft_lstprint_tokens(*token, "Print subshell");
	return (true);
}
