/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:17:56 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/21 15:41:39 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(const char *s1, const char *s2, t_joinfree jfree)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (jfree == FIRST || jfree == BOTH)
		free((char *)s1);
	if (jfree == SECOND || jfree == BOTH)
		free((char *)s2);
	return (join);
}
