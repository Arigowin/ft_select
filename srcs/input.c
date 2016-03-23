/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:15 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:15 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>

int		ft_input(t_input input[9], t_all *all)
{
	int			buf;
	int			i;
	int			ret;

	buf = 0;
	if (read(0, (char *)&buf, 3) == -1)
		return (-1);
	i = 0;
	while (i < 9 && buf != (input[i]).value)
		i++;
	if (i < 9 && buf == (input[i]).value)
	{
		if ((ret = (input[i]).fun(all)) == -1)
			return (-1);
		else if (ret == -2)
			return (-2);
	}
	return (0);
}
