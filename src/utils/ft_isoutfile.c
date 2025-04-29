/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoutfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:37:08 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/29 14:40:04 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_outfile(t_token *token)
{
	return (is_operator(token, ">") || is_operator(token, ">>")
		|| is_operator(token, "2>") || is_operator(token, ">2")
		|| is_operator(token, "&>") || is_operator(token, ">&")
		|| is_operator(token, "2>>") || is_operator(token, ">>2")
		|| is_operator(token, "&>>") || is_operator(token, ">>&"));
}
