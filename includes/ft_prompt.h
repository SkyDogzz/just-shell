/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:26:19 by yandry            #+#    #+#             */
/*   Updated: 2025/06/21 14:18:19 by yandry           ###   ########.fr       */
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

# define MAX_PROMPT_LEN 4096

# define HOST_ROOT "nasa (%s)"
# define HOST_REGULAR "%s"
# define SIGNAL_WITH_DESC "🗲 - %s (%s)"
# define SIGNAL_SIMPLE "🗲 - %s"
# define SIGNAL_NONE "🗲 - NA"

const char	*get_prompt_main(t_list *env, int last_exit);
const char	*get_prompt_user(t_list *env);
const char	*get_prompt_host(t_list *env);
const char	*get_prompt_path(t_list *env);
const char	*get_prompt_last_exit(int last_exit, bool include_desc);
const char	*get_exited_status(int status);
const char	*get_signaled_status(int status, bool include_desc);

#endif
