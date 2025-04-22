/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:02:19 by yandry            #+#    #+#             */
/*   Updated: 2025/04/22 18:16:07 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "../libft/includes/libft.h"
# include "stdbool.h"

typedef struct s_env
{
	char	*name;
	char	*value;
	bool	exported;
}	t_env;

// utils
void	clear_env(void *env);
bool	is_env(t_list *node, const char *name);

// init
t_list	*ft_init_env(const char **env);
void	ft_clear_env(t_list *env);

// crud moment, yippie (end me)
void	ft_new_env(t_list **env, const char *name, const char *value,
			bool exported);
t_env	*ft_get_env(t_list *env, const char *name);
void	ft_update_env(t_list **env, const char *name, const char *newval,
			bool exported);
void	ft_delete_env(t_list **env, const char *name);

#endif
