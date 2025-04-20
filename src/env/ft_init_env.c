/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:58 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 16:57:56 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

void	ft_free_arr(void ***array)
{
	size_t	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
	*array = NULL;
}

t_list	*ft_init_env(const char **env)
{
	t_list		*env_list;
	int			i;
	char		**splitted_env;
	const char	*default_env[] = {
		"PATH=/usr/local/bin:/usr/bin",
		"SHLVL=1",
		NULL};

	if (!env)
		return (ft_init_env(default_env));
	i = 0;
	env_list = NULL;
	while (env[i])
	{
		splitted_env = ft_split(env[i], '=');
		ft_new_env(&env_list, splitted_env[0], splitted_env[1]);
		ft_free_arr((void ***)&splitted_env);
		i++;
	}
	return (env_list);
}
