/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_leaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:11:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/10 13:56:56 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmp_leaf(void *s1, void *s2)
{
	static int	a = 1;

	if (a == 1)
		a = -1;
	else
		a = 1;
	return (a);
	(void) s1;
	(void) s2;
}
