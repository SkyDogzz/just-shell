/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_logical.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:07:47 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/15 15:07:57 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_logical(t_token *token)
{
	if (token->token_type != T_OPERATOR)
		return (false);
	if (ft_strcmp(token->content, "||") == 0
		|| ft_strcmp(token->content, "&&") == 0)
		return (true);
	return (false);
}
