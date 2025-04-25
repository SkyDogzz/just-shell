/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:15:07 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:17:09 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEREDOC_H
# define FT_HEREDOC_H

# include "minishell.h"
# include "ft_utils.h"
# include "ft_prompt.h"

int		ft_handle_heredocs(t_list *env, t_list **lst);
char	*ft_read_heredoc(const char *delimiter);

#endif
