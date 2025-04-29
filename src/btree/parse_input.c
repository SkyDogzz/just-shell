/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:13:16 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/29 15:13:27 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*parse_infile(t_list *tokens, t_list *redirs)
{
	t_token	*next;
	t_token	*act;
	t_redir	*redir;

	if (!tokens || !tokens->next)
		return (redirs);
	act = tokens->content;
	next = tokens->next->content;
	if (!act || !next)
		return (redirs);
	if (is_operator(act, "<"))
	{
		redir = (t_redir *)malloc(sizeof(t_redir));
		redir->file = ft_strdup(next->content);
		redir->type = REDIR_INPUT;
		ft_lstadd_back(&redirs, ft_lstnew(redir));
	}
	return (redirs);
}

static t_list	*parse_heredoc(const t_list *tokens, t_list *redirs)
{
	t_token	*token;
	t_redir	*redir;

	token = tokens->content;
	if (token->token_type == T_HEREDOC)
	{
		redir = (t_redir *)malloc(sizeof(t_redir));
		redir->file = ft_strdup(token->content);
		redir->type = REDIR_HEREDOC;
		ft_lstadd_back(&redirs, ft_lstnew(redir));
	}
	return (redirs);
}

t_list	*parse_input(t_list *tokens, t_list *redirs)
{
	while (tokens)
	{
		redirs = parse_infile(tokens, redirs);
		redirs = parse_heredoc(tokens, redirs);
		tokens = tokens->next;
	}
	return (redirs);
}
