/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:21:13 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/25 20:29:42 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

int	dupv2(int fd)
{
	int	ret;

	ret = dup(fd);
	ioctl(ret, FIOCLEX);
	return (ret);
}

int	dup2v2(int fd, int fd2)
{
	int	ret;

	ret = dup2(fd, fd2);
	ioctl(fd, FIOCLEX);
	return (ret);
}

int	pipev2(int *pipedes)
{
	int	ret;

	ret = pipe(pipedes);
	ioctl(pipedes[0], FIOCLEX);
	ioctl(pipedes[1], FIOCLEX);
	return (ret);
}
