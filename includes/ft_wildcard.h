/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:31:27 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/28 17:46:02 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WILDCARD_H
# define FT_WILDCARD_H

# include "minishell.h"

bool	ft_expand_wildcard(t_list **tokens, t_token *dup);
bool	advanced_wildcard(t_list **tokens, t_token *dup);

#endif
