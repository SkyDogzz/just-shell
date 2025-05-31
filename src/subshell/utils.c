/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:09:30 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/31 10:09:42 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_verif_after_paren(t_list *tokens)
{
	t_token	*token;
	bool	iscloser;

	iscloser = false;
	while (tokens)
	{
		token = tokens->content;
		if (iscloser && token->token_type == T_WORD)
			return (false);
		if (token->token_type == T_SUBSTITUTE && token->content[0] == ')')
			iscloser = true;
		tokens = tokens->next;
	}
	return (true);
}
