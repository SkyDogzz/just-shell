/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_user_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:43:15 by yandry            #+#    #+#             */
/*   Updated: 2025/04/25 19:02:01 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

const char	*get_prompt_user(t_list *env)
{
	char	*user;

	(void)env;
	user = getenv("USER");
	if (!user)
		return (ft_strdup("unknown"));
	return (ft_strdup(user));
}
