/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:02:11 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/28 18:33:37 by tstephan         ###   ########.fr       */
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

static void	ft_expand_utils(t_list *env, t_list **tokens, t_list *act)
{
	t_token	*dup;

	dup = malloc(sizeof(t_token));
	if (!dup)
		return ;
	dup->content = ft_strdup(act->content);
	dup->token_type = ft_gettype(dup->content);
	dup = ft_expand(env, dup);
	dup = ft_remove_quote(dup);
	if (ft_expand_wildcard(tokens, dup))
	{
		free(dup->content);
		free(dup);
		return ;
	}
	if (ft_strcmp(dup->content, "") != 0)
		ft_lstadd_back(tokens, ft_lstnew(dup));
	else
	{
		free(dup->content);
		free(dup);
	}
}

t_list	*ft_string_to_token(t_list *env, t_list *tokens, t_list *pre_tokens)
{
	t_list	*act;

	act = pre_tokens;
	while (act)
	{
		ft_expand_utils(env, &tokens, act);
		act = act->next;
	}
	return (tokens);
}
