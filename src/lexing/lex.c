/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:22 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/20 16:51:48 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token_type	ft_gettype(char *s)
{
	if (ft_strlen(s) == 1 && ft_isspace(s[0]))
		return (T_BLANK);
	else if (ft_strlen(s) == 1 && ft_isin_charset(s[0], OPERATOR_S))
		return (T_OPERATOR);
	else if (ft_isin_stringset(s, OPERATOR_M, ','))
		return (T_OPERATOR);
	else if (ft_isin_stringset(s, RESERVED, ','))
		return (T_RESERVED);
	else if (ft_isin_stringset(s, SUBSTITUTE, ','))
		return (T_SUBSTITUTE);
	else if (s[0] == '\'')
		return (T_QUOTE);
	else if (s[0] == '"')
		return (T_EXPANSION);
	return (T_WORD);
}

t_list	*ft_string_to_token(t_list *tokens, t_list *pre_tokens)
{	
	t_list	*act;
	t_token	*dup;

	act = pre_tokens;
	while (act)
	{
		dup = NULL;
		dup = malloc(sizeof(t_token));
		if (!dup)
			return (tokens);
		dup->content = ft_strdup(act->content);
		dup->token_type = ft_gettype(dup->content);
		dup = ft_expand(dup);
		dup = ft_remove_quote(dup);
		if (ft_strcmp(dup->content, "") != 0)
			ft_lstadd_back(&tokens, ft_lstnew(dup));
		else
		{
			free(dup->content);
			free(dup);
		}
		act = act->next;
	}
	return (tokens);
}

static bool	handle_heredoc_error(t_list **tokens)
{
	int	error;

	error = ft_handle_heredocs(tokens);
	if (error)
	{
		if (error == HEREDOC_PARSE_ERROR)
		{
			printf("Syntax error near unexpected token\n");
			ft_lstclear(tokens, ft_lstclear_t_token);
			return (true);
		}
		if (error == HEREDOC_SIGINT)
		{
			ft_lstclear(tokens, ft_lstclear_t_token);
			return (true);
		}
	}
	return (false);
}

static t_list	*ft_remove_spaces(t_list *tokens)
{
	t_list	*act;
	t_token	*act_t;
	t_list	*mem;

	act = tokens;
	while (act && act->next)
	{
		act_t = act->next->content;
		if (act_t->token_type == T_BLANK)
		{
			mem = act->next;
			act->next = act->next->next;
			ft_lstclear_t_token(mem->content);
			free(mem);
		}
		act = act->next;
	}
	return (tokens);
}

t_list	*ft_lex(const char *input)
{
	t_list	*tokens;
	t_list	*pre_tokens;

	pre_tokens = ft_doom_split(input);
	if (!pre_tokens)
		return (NULL);
	pre_tokens = ft_remove_whitespace(pre_tokens);
	tokens = NULL;
	tokens = ft_string_to_token(tokens, pre_tokens);
	ft_lstclear(&pre_tokens, ft_lstclear_string);
	tokens = ft_fuse_word(tokens);
	if (handle_heredoc_error(&tokens))
		return (NULL);
	tokens = ft_remove_spaces(tokens);
	return (tokens);
}
