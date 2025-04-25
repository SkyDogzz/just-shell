/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:26:19 by yandry            #+#    #+#             */
/*   Updated: 2025/04/25 19:25:56 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROMPT_H
# define FT_PROMPT_H

# include "ft_utils.h"

//# define DEFAULT_PROMPT "$user @ $host in $path [ $last_exit ]\n~> "


# ifdef DEBUG
#  define DEFAULT_PROMPT "%s%s%s @ %s%s debugging in %s%s%s%s [ %s ]\n%s~>%s "
# else 
#  define DEFAULT_PROMPT "%s%s%s @ %s%s in %s%s%s%s [ %s ]\n%s~>%s "
# endif

# define HOST_ROOT "nasa (%s)"
# define HOST_REGULAR "%s"

typedef enum e_prompt
{
	PROMPT_MAIN,
	PROMPT_HEREDOC,
	PROMPT_QUOTE,
	PROMPT_SUBSHELL
}	t_prompt;

const char	*get_prompt_main(t_list *env);
const char	*get_prompt_user(t_list *env);
const char	*get_prompt_host(t_list *env);
const char	*get_prompt_path(t_list *env);
const char	*get_prompt_last_exit(void);

char		*ft_readline(t_prompt id, t_list *env);

#endif
