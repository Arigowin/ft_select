/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:14 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/24 15:53:19 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				enter(t_all *all)
{
	while (all->elem->head == FALSE)
		all->elem = all->elem->next;
	return (-2);
}

static int		calc_right(t_all *all)
{
	int		i;
	int		stop;
	float	tmp;
	int		tmp2;

	tmp = 0.0 + ((float)all->win.nb_elem / (float)all->win.nb_row);
	tmp2 = (all->win.nb_elem / all->win.nb_row);
	i = 0;
	stop = 0;
	if ((all->win.nb_elem / all->win.nb_row) > 0)
	{
		stop = all->win.nb_row;
		if (tmp > tmp2)
		{
			tmp2++;
			i = 1;
		}
		if (((all->point.x / all->win.col_size) + i) == tmp2)
			stop -= (stop - (all->win.nb_elem % all->win.nb_row));
		else if (((all->point.x / all->win.col_size) + i) == tmp2 - 1)
			if (all->point.y >= (all->win.nb_elem % all->win.nb_row))
				stop += (all->win.nb_elem % all->win.nb_row);
	}
	return (stop);
}

int				right(t_all *all)
{
	int		i;
	int		stop;

	stop = calc_right(all);
	i = 0;
	all->show = 0;
	while (i < stop)
	{
		if (i == stop - 1)
			all->show = 1;
		if (next(all) == -1)
			return (-1);
		i++;
	}
	all->show = 1;
	return (0);
}

static int		calc_left(t_all *all)
{
	int		stop;

	stop = 0;
	if ((all->win.nb_elem / all->win.nb_row) > 0)
	{
		stop = all->win.nb_row;
		if (all->point.x == 0)
		{
			if (all->point.y >= (all->win.nb_elem % all->win.nb_row))
				stop += (all->win.nb_elem % all->win.nb_row);
			else
				stop -= (stop - (all->win.nb_elem % all->win.nb_row));
		}
	}
	return (stop);
}

int				left(t_all *all)
{
	int		i;
	int		stop;

	i = 0;
	stop = calc_left(all);
	all->show = 0;
	while (i < stop)
	{
		if (i == stop - 1)
			all->show = 1;
		if (prev(all) == -1)
			return (-1);
		i++;
	}
	all->show = 1;
	return (0);
}
