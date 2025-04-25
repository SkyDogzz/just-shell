/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:49:34 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:52:21 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_H
# define FT_PARSE_H

# include "minishell.h"
# include "ft_btree.h"
# include "ft_prompt.h"
# include "ft_lst_helper.h"
# include "ft_signals.h"

t_btree	*ft_parse(t_list *tokens);
void	ft_free_leaf(void *leaf);
bool	ft_findsubshell(t_list *env, t_list **tokens);
char	*ft_read_subshell(int level);
char	*ft_handle_multiline_quote(char *input);
t_leaf	*ft_create_leaf(t_node_type type, char	**args);

#endif
