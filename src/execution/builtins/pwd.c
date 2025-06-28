/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:28:03 by yandry            #+#    #+#             */
/*   Updated: 2025/06/28 18:25:18 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include <linux/limits.h>

int	ft_pwd(const t_cmd *cmd, t_list *env)
{
	char	cwd[PATH_MAX];

	(void)cmd;
	(void)env;
	if (!getcwd(cwd, sizeof cwd))
		*cwd = 0;
	if (!*cwd)
	{
		ft_dprintf(STDERR_FILENO, "the void *dun dun dun*\n");
		return (1 << 8);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
