/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:28 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/18 16:42:47 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit;

int	main(int argc, char *argv[], char *argp[])
{
	int		exit_code;

	ft_set_sigaction();
	g_exit = 0;
	exit_code = ft_sinistre(argp);
	rl_clear_history();
	return (exit_code);
	(void) argc;
	(void) argv;
}
