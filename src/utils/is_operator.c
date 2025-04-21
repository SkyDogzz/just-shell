/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:23:11 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/21 15:39:56 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(const t_token *token, const char *op)
{
	if (token->token_type != T_OPERATOR)
		return (false);
	if (ft_strcmp(token->content, op) == 0)
		return (true);
	return (false);
}
