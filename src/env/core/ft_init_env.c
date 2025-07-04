/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:58 by yandry            #+#    #+#             */
/*   Updated: 2025/07/04 17:55:28 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

t_list	*ft_init_env(const char **env)
{
	t_list		*env_list;
	int			i;
	char		**splitted_env;
	const char	*default_env[] = {
		"PATH=/usr/local/bin:/usr/bin",
		NULL};

	if (!env || !env[0])
		return (ft_init_env(default_env));
	i = 0;
	env_list = NULL;
	while (env[i])
	{
		splitted_env = ft_split(env[i], '=');
		ft_new_env(&env_list, splitted_env[0],
			ft_strchr(env[i], '=') + 1, true);
		ft_free_array((void ***)&splitted_env);
		i++;
	}
	return (env_list);
}
