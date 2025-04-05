/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:46 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/20 16:47:48 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_pipe(t_token *token)
{
	return (ft_strlen(token->content) == 1 && token->token_type == T_OPERATOR
		&& ft_strcmp(token->content, "|") == 0);
}
