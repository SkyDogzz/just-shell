/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:28:03 by yandry            #+#    #+#             */
/*   Updated: 2025/04/22 17:35:11 by yandry           ###   ########.fr       */
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
	ft_printf("%s\n", cwd);
	return (0);
}
