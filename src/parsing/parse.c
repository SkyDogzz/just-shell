/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:22 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/17 20:11:21 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_string	*ft_doom_split(const char *input)
{
	t_string	*top;
	char		*dup;
	t_quote		quote;
	int			len;

	quote = UNQUOTED;
	top = NULL;
	while (*input)
	{
		if (!quote)
		{
			len = is_in_stringset(input, OPERATOR_M, ',');
			if (!len)
				len = is_in_stringset(input, RESERVED, ',');
			if (!len)
				len = is_in_stringset(input, SUBSTITUTE, ',');
			if (!len)
				len = is_in_charset(*input, OPERATOR_S);
			if (!len)
				len = 1;
		}
		dup = ft_strndup(input, len);
		if (!dup)
			continue ;
		top = string_add_bottom(top, string_create(dup));
		free(dup);
		input += len;
	}
	if (!top)
		return (NULL);
	return (top);
}

t_token	*parse_tokens(char *input)
{
	t_token		*tokens;
	t_string	*pre_tokens;
	t_string	*act;

	pre_tokens = ft_doom_split(input);
	if (!pre_tokens)
		return (NULL);
	tokens = NULL;
	act = pre_tokens;
	while (act)
	{
		tokens = token_add_bottom(tokens, token_create(act->content, 0));
		act = act->next;
	}
	string_free(pre_tokens);
	token_print(tokens);
	return (tokens);
	(void) input;
}
