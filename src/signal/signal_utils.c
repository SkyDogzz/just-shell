/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:28:38 by yandry            #+#    #+#             */
/*   Updated: 2025/06/21 14:31:59 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signals.h"
#include "minishell.h"

void	set_sigpair(t_sig_pair *pair, const char *name, const char *desc)
{
	ft_strlcpy(pair->signal_name, name, 16);
	ft_strlcpy(pair->signal_description, desc, 32);
}

const t_sig_pair	*get_signal(int sig_no)
{
	const t_signal	*sig = g_signals;
	char			rt_buffer[16];
	t_sig_pair		*sig_pair;

	sig_pair = ft_calloc(sizeof(t_sig_pair), 1);
	if (!sig_pair)
		return (NULL);
	if (sig_no >= SIGRTMIN && sig_no <= SIGRTMAX)
	{
		ft_snprintf(rt_buffer, sizeof(rt_buffer),
			"SIGRT_%d", sig_no - SIGRTMIN);
		set_sigpair(sig_pair, rt_buffer, "Real-time signal");
		return (sig_pair);
	}
	while (sig->sig_name)
	{
		if (sig->sig_no == sig_no)
		{
			set_sigpair(sig_pair, sig->sig_name, sig->sig_desc);
			return (sig_pair);
		}
		sig++;
	}
	free(sig_pair);
	return (NULL);
}
