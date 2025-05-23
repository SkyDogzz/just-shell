/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:34:33 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/29 15:14:51 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_redir(t_list *tokens)
{
	t_list	*redirs;

	redirs = NULL;
	redirs = parse_input(tokens, redirs);
	redirs = parse_outilfe(tokens, redirs);
	return (redirs);
}
