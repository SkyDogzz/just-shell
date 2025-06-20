/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 10:27:52 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_env.h"
#include <stdlib.h>

int	g_exit = 0;

int	tty_shell(t_list *env);

int	main(int argc, char *argv[], char *argp[])
{
	t_list	*env;
	int		final_ret;
	int		(*shell_mode)(t_list *env);

	env = ft_init_env((const char **)argp);
	shell_mode = tty_shell;
	final_ret = shell_mode(env);
	ft_clear_env(env);
	exit(final_ret);
	(void) argc;
	(void) argv;
}
