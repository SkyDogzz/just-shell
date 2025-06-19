/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/19 02:30:40 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_env.h"
#include <stdlib.h>

int	g_exit = 0;

/**
 * We are in interactive mode. Make sure to show a neat little prompt
 * and everything the user needs to not want to die while using our shell
 */
int	tty_shell(t_list *env);

/**
 * Non-interactive mode. We're free to run shit like we want without
 * having to worry about giving some sort of feedback to the user.
 * They better know how to write scripts.
 */
int	non_tty_shell(t_list *env);

int	main(int argc, char *argv[], char *argp[])
{
	t_list	*env;
	int		final_ret;
	int		(*shell_mode)(t_list *env);

	env = ft_init_env((const char **)argp);
	if (isatty(STDIN_FILENO))
		shell_mode = tty_shell;
	else
		shell_mode = tty_shell;
	final_ret = shell_mode(env);
	ft_clear_env(env);
	exit(final_ret);
	(void) argc;
	(void) argv;
}
