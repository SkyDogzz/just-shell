/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:33:01 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/02 18:33:02 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_conseq_ope(t_list *tokens, const char *s1, const char *s2)
{
	t_token	*tok1;
	t_token	*tok2;

	if (!tokens || !tokens->next)
		return (true);
	tok1 = tokens->content;
	tok2 = tokens->next->content;
	if (tok1->token_type != T_OPERATOR || tok2->token_type != T_OPERATOR)
		return (true);
	if (ft_strcmp(tok1->content, s1) == 0 && ft_strcmp(tok2->content, s2) == 0)
		return (true);
	return (false);
}
