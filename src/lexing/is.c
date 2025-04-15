/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:46 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/05 15:42:26 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_pipe(t_token *token)
{
	return (ft_strlen(token->content) == 1 && token->token_type == T_OPERATOR_S
		&& ft_strcmp(token->content, "|") == 0);
}
