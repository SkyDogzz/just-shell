/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:42:44 by skydogzz          #+#    #+#             */
/*   Updated: 2025/04/28 07:17:14 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORY_H
# define FT_HISTORY_H

# include <fcntl.h>
# include <stdlib.h>
# include "minishell.h"

# define HISTORY_FILE "~/.sshxx_history"

void	retreive_history(t_list *env);
void	store_history(char *input, t_list *env);

#endif
