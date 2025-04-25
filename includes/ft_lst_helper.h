/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_helper.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:40:57 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:41:49 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_HELPER_H
# define FT_LST_HELPER_H

# include "minishell.h"

void	ft_lstclear_string(void *content);
void	ft_lstprint_string(const t_list *lst, const char *s);
void	ft_lstclear_t_token(void *content);
void	ft_lstprint_tokens(t_list *lst, const char *s);
void	ft_lstclear_pipes(void *content);
void	ft_lstprint_pipes(t_list *lst, const char *s);

#endif
