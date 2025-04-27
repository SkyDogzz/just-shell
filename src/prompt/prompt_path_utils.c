/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:46:39 by yandry            #+#    #+#             */
/*   Updated: 2025/04/27 10:59:02 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_env.h"
#include <linux/limits.h>

static char	*get_current_wd(void)
{
	char	*cwd;

	cwd = ft_calloc(PATH_MAX, sizeof(char));
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAX) != NULL)
		return (cwd);
	return (NULL);
}

const char	*get_prompt_path(t_list *env)
{
	char	*fullpath;
	char	*relative;
	t_env	*home_env;

	fullpath = get_current_wd();
	if (!fullpath)
		return (NULL);
	home_env = ft_get_env(env, "HOME");
	if (home_env)
		relative = ft_strreplace(fullpath, home_env->value, "~");
	else
		relative = ft_strdup(fullpath);
	free(fullpath);
	return (relative);
}
