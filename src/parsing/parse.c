/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:22 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/25 16:54:18 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_doom_split(const char *input)
{
	t_list				*top;
	char				*dup;
	int					len;
	static t_quote		quote = UQUOTE;

	top = NULL;
	while (input && *input)
	{
		if (!quote && ft_isin_charset(*input, QUOTE))
		{
			quote = SQUOTE;
			if (*input == '"')
				quote = DQUOTE;
			continue ;
		}
		if (!quote)
		{
			len = ft_isin_stringset(input, OPERATOR_M, ',');
			if (!len)
				len = ft_isin_stringset(input, RESERVED, ',');
			if (!len)
				len = ft_isin_stringset(input, SUBSTITUTE, ',');
			if (!len)
				len = ft_isin_charset(*input, OPERATOR_S);
			if (!len)
				len = 1;
		}
		else if(quote)
		{
			len = 1;
			int pos = 1;
			while (input[pos] && ((quote == SQUOTE && input[pos] != '\'') || (quote == DQUOTE && input[pos] != '"')))
			{
				len++;
				pos++;
			}
			if (input[pos] == '"' || input[pos] == '\'')
			{
				len++;
				quote = SQUOTE;
			}
		}
		dup = ft_strndup(input, len);
		if (!dup)
			continue ;
		ft_lstadd_back(&top, ft_lstnew(dup));
		input += len;
	}
	if (!top)
		return (NULL);
	return (top);
}

t_list	*ft_lex(const char *input)
{
	t_list	*tokens;
	t_list	*pre_tokens;
	t_list	*act;

	pre_tokens = ft_doom_split(input);
	if (!pre_tokens)
		return (NULL);
	tokens = NULL;
	act = pre_tokens;
	while (act)
	{
		ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(act->content)));
		act = act->next;
	}
	ft_lstclear(&pre_tokens, ft_lstclear_string);
	return (tokens);
}
