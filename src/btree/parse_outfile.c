/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:13:37 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/11 15:12:29 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_type(t_token *act, t_token *next, t_list **tokens,
		t_list **redirs)
{
	t_redir	*redir;

	if (ft_is_outfile(act))
	{
		redir = (t_redir *)malloc(sizeof(t_redir));
		if (!redir)
			return ;
		redir->file = ft_strdup(next->content);
		if (is_operator(act, ">"))
			redir->type = REDIR_TRUNC_STDOUT;
		else if (is_operator(act, ">>"))
			redir->type = REDIR_APPEND_STDOUT;
		else if (is_operator(act, "2>") || is_operator(act, ">2"))
			redir->type = REDIR_TRUNC_STDERR;
		else if (is_operator(act, "2>>") || is_operator(act, ">>2"))
			redir->type = REDIR_APPEND_STDERR;
		else if (is_operator(act, "&>") || is_operator(act, ">&"))
			redir->type = REDIR_TRUNC_STDALL;
		else
			redir->type = REDIR_APPEND_STDALL;
		ft_lstadd_back(redirs, ft_lstnew(redir));
		*tokens = (*tokens)->next;
	}
}

t_list	*parse_outilfe(t_list *tokens, t_list *redirs)
{
	t_token	*act;
	t_token	*next;

	while (tokens && tokens->next)
	{
		act = tokens->content;
		next = tokens->next->content;
		if (!act || !next)
			return (redirs);
		find_type(act, next, &tokens, &redirs);
		tokens = tokens->next;
	}
	return (redirs);
}
