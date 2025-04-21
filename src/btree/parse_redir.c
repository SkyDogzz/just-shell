/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:34:33 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/18 16:01:24 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*parse_infile(t_list *tokens, t_list *redirs)
{
	const t_token	*next;
	t_token			*act;
	t_redir			*redir;

	while (tokens && tokens->next)
	{
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
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (redirs);
}

static t_list	*parse_heredoc(t_list *tokens, t_list *redirs)
{
	const t_token	*token;
	t_redir			*redir;

	while (tokens)
	{
		token = tokens->content;
		if (token->token_type == T_HEREDOC)
		{
			redir = (t_redir *)malloc(sizeof(t_redir));
			redir->file = ft_strdup(token->content);
			redir->type = REDIR_HEREDOC;
			ft_lstadd_back(&redirs, ft_lstnew(redir));
		}
		tokens = tokens->next;
	}
	return (redirs);
}

static t_list	*parse_outilfe(t_list *tokens, t_list *redirs)
{
	t_token	*act;
	t_token	*next;
	t_redir	*redir;

	while (tokens && tokens->next)
	{
		act = tokens->content;
		next = tokens->next->content;
		if (!act || !next)
			return (redirs);
		if (is_operator(act, ">") || is_operator(act, ">>"))
		{
			redir = (t_redir *)malloc(sizeof(t_redir));
			redir->file = ft_strdup(next->content);
			if (is_operator(act, ">"))
				redir->type = REDIR_TRUNC;
			else
				redir->type = REDIR_APPEND;
			ft_lstadd_back(&redirs, ft_lstnew(redir));
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (redirs);
}

t_list	*parse_redir(t_list *tokens)
{
	t_list	*redirs;

	redirs = NULL;
	redirs = parse_infile(tokens, redirs);
	redirs = parse_heredoc(tokens, redirs);
	redirs = parse_outilfe(tokens, redirs);
	return (redirs);
}
