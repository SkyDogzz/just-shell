/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:02:11 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/16 18:46:00 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_wildcard.h"

static t_token_type	ft_gettype(const char *s)
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

static void	ft_post_expand(t_token *dup, t_list **tokens)
{
	t_list	*mem;
	t_list	*token;

	token = ft_doom_split(dup->content);
	free(dup->content);
	free(dup);
	while (token)
	{
		dup = malloc(sizeof(t_token));
		dup->content = ft_strdup(token->content);
		dup->token_type = ft_gettype(dup->content);
		ft_lstadd_back(tokens, ft_lstnew(dup));
		mem = token;
		token = token->next;
		free(mem->content);
		free(mem);
	}
}

static void	ft_expand_utils(t_list *env, t_list **tokens, t_list *act,
		int status)
{
	t_token	*dup;

	dup = malloc(sizeof(t_token));
	if (!dup)
		return ;
	dup->content = ft_strdup(act->content);
	dup->token_type = ft_gettype(dup->content);
	dup = ft_expand(env, dup, status);
	dup = ft_remove_quote(dup);
	if (ft_expand_wildcard(tokens, dup))
	{
		free(dup->content);
		free(dup);
		return ;
	}
	if (dup->token_type == T_POSTEXPANSION && ft_strchr(dup->content, ' '))
		ft_post_expand(dup, tokens);
	else if (ft_strcmp(dup->content, "") != 0)
		ft_lstadd_back(tokens, ft_lstnew(dup));
	else
	{
		free(dup->content);
		free(dup);
	}
}

t_list	*ft_string_to_token(t_list *env, t_list *tokens, t_list *pre_tokens,
		int status)
{
	t_list	*act;

	act = pre_tokens;
	while (act)
	{
		ft_expand_utils(env, &tokens, act, status);
		act = act->next;
	}
	return (tokens);
}
