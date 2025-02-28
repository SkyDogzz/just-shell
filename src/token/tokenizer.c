/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:31:14 by yandry            #+#    #+#             */
/*   Updated: 2025/02/28 19:36:40 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	identify_token(t_token *token)
{
	size_t	i;

	i = 0;
	while (token->content[i])
	{
		if (is_in_charset(token->content[i], OPERATOR_S))
			token->token_type = T_OPERATOR;
		else
			token->token_type = T_WORD;
		i++;
	}
}

t_token	*ft_new_token(const char *content)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->content = (char *)content;
	identify_token(tok);
	return (tok);
}
