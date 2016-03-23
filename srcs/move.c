/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:16 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:16 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int		gobeginogline(int x, int y)
{
	char	*res;

	if ((res = tgetstr("cm", NULL)) == NULL)
		return (-1);
	tputs(tgoto(res, x, y), 1, my_outc);
	return (0);
}
