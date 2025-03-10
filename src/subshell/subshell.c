/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:19 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/10 17:17:01 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*https://unix.stackexchange.com/questions/442692/is-a-subshell*/

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
		}
		act = act->next;
	}
}

bool	ft_findsubshell(t_list **token)
{
	t_list	*act;
	t_token	*act_t;
	int		level;
	t_token	*nt;

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
		nt = (t_token *)malloc(sizeof(t_token));
		nt->content = ft_read_subshell(level);
		nt->token_type = T_SUBSTITUTE;
		ft_lstadd_back(token, ft_lstnew(nt));
	}
	ft_group_subshell(token);
	ft_lstprint_tokens(*token, "Print subshell");
	return (true);
}
