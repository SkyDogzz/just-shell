/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:35:17 by yandry            #+#    #+#             */
/*   Updated: 2025/04/23 14:18:02 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include "minishell.h"

typedef struct s_builtin
{
	const char	*name;
	int			(*func)(const t_cmd*, t_list *env);
}	t_builtin;

int	ft_echo(const t_cmd *cmd, t_list *env);
int	ft_cd(const t_cmd *cmd, t_list *env);
int	ft_pwd(const t_cmd *cmd, t_list *env);
int	ft_export(const t_cmd *cmd, t_list *env);
int	ft_unset(const t_cmd *cmd, t_list *env);
int	ft_env(const t_cmd *cmd, t_list *env);
int	ft_exit(const t_cmd *cmd, t_list *env);

static const t_builtin	g_builtins[] = {
{.name = "echo", .func = ft_echo},
{.name = "cd", .func = ft_cd},
{.name = "pwd", .func = ft_pwd},
{.name = "export", .func = ft_export},
{.name = "unset", .func = ft_unset},
{.name = "env", .func = ft_env},
{.name = "exit", .func = ft_exit},
{.name = NULL, .func = NULL}
};

#endif
