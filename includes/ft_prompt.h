/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:26:19 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 22:30:18 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROMPT_H
# define FT_PROMPT_H

# include "../libft/includes/libft.h"

//# define DEFAULT_PROMPT "$user @ $host in $path [ $last_exit ]\n~> "

# ifdef DEBUG
#  define DEFAULT_PROMPT "%s%s%s @ %s%s debugging in %s%s%s%s [ %s ]\n%s~>%s "
# else 
#  define DEFAULT_PROMPT "%s%s%s @ %s%s in %s%s%s%s [ %s ]\n%s~>%s "
# endif

# define HOST_ROOT "nasa (%s)"
# define HOST_REGULAR "%s"

const char	*get_prompt_main(t_list *env);
const char	*get_prompt_user(t_list *env);
const char	*get_prompt_host(t_list *env);
const char	*get_prompt_path(t_list *env);
const char	*get_prompt_last_exit(void);

#endif
