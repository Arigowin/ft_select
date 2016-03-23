/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:17 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:17 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_select.h"

int		ft_signal(void)
{
	int i;

	i = 1;
	while (i < 32)
	{
		signal(i, signalhandler);
		i++;
	}
	return (1);
}
