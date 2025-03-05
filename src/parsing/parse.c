/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:22 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 17:32:12 by tstephan         ###   ########.fr       */
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

static t_list	*ft_string_to_token(t_list *tokens, t_list *pre_tokens)
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
		if (ft_strncmp(dup->content, "", ft_strlen(dup->content) != 0))
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
	ft_lstprint_string(pre_tokens, "Print strings :");
	ft_lstclear(&pre_tokens, ft_lstclear_string);
	tokens = ft_fuse_word(tokens);
	return (tokens);
}
