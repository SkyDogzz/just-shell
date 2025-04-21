/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:05:21 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/18 16:28:25 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_replace_heredoc(t_list *lst, char *content)
{
	t_list	*act;
	t_token	*act_t;
	char	*mem;

	act = lst;
	while (act)
	{
		act_t = (t_token *)act->content;
		if (is_operator(act_t, "<<"))
		{
			mem = act_t->content;
			act_t->content = content;
			act_t->token_type = T_HEREDOC;
			act_t = ft_expand(act_t);
			act->content = act_t;
			free(mem);
			return (lst);
		}
		act = act->next;
	}
	return (lst);
}

static int	ft_handle_heredoc(t_list *act, t_list **lst)
{
	t_token	*next_t;
	char	*delimiter;
	char	*content;

	if (!act->next)
		return (HEREDOC_PARSE_ERROR);
	next_t = (t_token *)act->next->content;
	if (next_t->token_type == T_BLANK)
	{
		if (!act->next->next)
			return (HEREDOC_PARSE_ERROR);
		next_t = act->next->next->content;
	}
	if (next_t->token_type != T_WORD)
		return (HEREDOC_PARSE_ERROR);
	delimiter = next_t->content;
	content = ft_read_heredoc(delimiter);
	if (!content)
		return (HEREDOC_SIGINT);
	*lst = ft_replace_heredoc(*lst, content);
	return (0);
}

int	ft_handle_heredocs(t_list **lst)
{
	t_list	*act;
	t_token	*act_t;
	int		error;

	act = *lst;
	while (act)
	{
		act_t = (t_token *)act->content;
		if (is_operator(act_t, "<<"))
		{
			error = ft_handle_heredoc(act, lst);
			if (error)
				return (error);
		}
		act = act->next;
	}
	return (0);
}
