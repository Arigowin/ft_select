/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:16 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:16 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		memoire_fd(int fd)
{
	static int	tmp;

	if (fd != 0)
		tmp = fd;
	return (tmp);
}

t_all	*memoire(t_all *all, int code)
{
	static t_all *tmp;

	if (code == 0)
		tmp = all;
	return (tmp);
}
