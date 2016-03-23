/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tputs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:17 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:17 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"

int	my_outc(int c)
{
	int		fd;

	fd = 0;
	fd = memoire_fd(fd);
	ft_putchar_fd(c, fd);
	return (0);
}
