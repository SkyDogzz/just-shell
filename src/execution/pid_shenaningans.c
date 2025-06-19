/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_shenaningans.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:33:49 by yandry            #+#    #+#             */
/*   Updated: 2025/06/19 12:35:39 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

static int	*get_pid_array(void)
{
	static int	pids[MAX_PIDS_WAIT];
	static int _init = 0;
	int			i;

	i = 0;
	if (!_init)
	{
		while (i < MAX_PIDS_WAIT)
			pids[i++] = -1;
		_init = 1;
	}
	return (pids);
}

void	operate_on_pid_list(t_pid_op op, int pid)
{
	static long	current_id = 0;
	int			*pids;

	pids = get_pid_array();
	if (current_id < 0)
		current_id = 0;
	if (current_id > MAX_PIDS_WAIT)
		exit(-1);
	if (op == OP_INSERT)
		pids[current_id++] = pid;
	else if (op == OP_DELETE)
		pids[current_id--] = -1;
}

void	wait_all(int *status)
{
	int *pids;
	int	highest_pid;
	int	state;
	int	i;

	pids = get_pid_array();
	highest_pid = -1;
	state = 0;
	i = 0;
	while (i < MAX_PIDS_WAIT)
	{
		if (pids[i] != -1)
		{
			waitpid(pids[i], &state, 0);
			if (highest_pid < pids[i])
			{
				*status = state;
				highest_pid = pids[i];
			}
			ft_dprintf(STDERR_FILENO, "%d's exit status: %d\n", pids[i], WEXITSTATUS(*status));
		}
		pids[i++] = -1;
	}
}
