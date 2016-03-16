#include "ft_select.h"

int				escape(t_all *all)
{
	(void)all;
	return (-1);
}

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

	tmp = 0.0 + ((float)all->win.nb_elem/(float)all->win.nb_row);
	tmp2 = (all->win.nb_elem/all->win.nb_row);
	i = 0;
	stop = 0;
	if ((all->win.nb_elem/all->win.nb_row) > 0)
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
	while (i < stop)
	{
		if (next(all) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int		calc_left(t_all *all)
{
	int		stop;

	stop = 0;
	if ((all->win.nb_elem/all->win.nb_row) > 0)
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
	while (i < stop)
	{
		if (prev(all) == -1)
			return (-1);
		i++;
	}
	return (0);
}
