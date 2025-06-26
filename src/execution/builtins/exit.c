/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:14:14 by yandry            #+#    #+#             */
/*   Updated: 2025/06/26 16:42:51 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "minishell.h"

#define INVALID_EXIT "ssh-xx: exit code isn't numeric. ignoring"
#define OVERFLW_EXIT "ssh-xx: exit code overflow (aaahh run away)"

static bool	is_numeric(const char *str)
{
	bool	is_valid;

	is_valid = false;
	while (*str)
	{
		is_valid = (*str >= '0' && *str <= '9');
		if (!is_valid)
			break ;
		str++;
	}
	return (is_valid);
}

static bool	atoverflow(const char *nptr, long *k)
{
	int	sign;

	*k = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -sign;
		nptr++;
	}
	while (ft_isdigit((int)*nptr))
		*k = (*k << 3) + (*k << 1) + (*nptr++) - '0';
	*k = *k * sign;
	return (*k < 0 || *k > 255);
}

static int	handle_exit_arg(const char *exit_code_str, long *exit_code)
{
	if (!is_numeric(exit_code_str))
	{
		ft_putendl_fd(INVALID_EXIT, STDERR_FILENO);
		return (2 | EXIT_SHELL);
	}
	if (atoverflow(exit_code_str, exit_code))
	{
		ft_putendl_fd(OVERFLW_EXIT, STDERR_FILENO);
		return (2 | EXIT_SHELL);
	}
	return (*exit_code | EXIT_SHELL);
}

int	ft_exit(const t_cmd *cmd, t_list *env)
{
	long	exit_code;
	t_env	*last_status;

	(void)env;
	if (cmd->args[1])
		return (handle_exit_arg(cmd->args[1], &exit_code));
	else
	{
		last_status = ft_get_env(env, "?");
		if (last_status && last_status->value)
			exit_code = ft_atoi(last_status->value) & 0xFF;
		else
			exit_code = 0;
	}
	return (exit_code | EXIT_SHELL);
}
