/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:46 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/18 14:03:47 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_pipe(t_token *token)
{
	return (ft_strlen(token->content) == 1 && token->token_type == T_OPERATOR
		&& ft_strncmp(token->content, "|", 1) == 0);
}
