/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:53:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:42:21 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEX_H
# define FT_LEX_H

# include "minishell.h"
# include "ft_btree.h"
# include "ft_heredoc.h"
# include "ft_lst_helper.h"

t_list	*ft_lex(t_list *env, const char *cmd_line);
t_list	*ft_fuse_word(t_list *lst);
t_token	*ft_remove_quote(t_token *token);
t_list	*ft_remove_whitespace(t_list *lst);

#endif
