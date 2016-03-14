#include "ft_select.h"

int		escape(t_all *all)
{
	(void)all;
	return (-1);
}

int		enter(t_all *all)
{
	while (all->elem->head == FALSE)
		all->elem = all->elem->next;
	return (-2);
}

#include <stdio.h>
int		right(t_all *all)
{
	int		i;
	int		stop;

	i = 0;
	stop = all->win.nb_row;
	while (i < stop)
	{
		if (next(all) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int		left(t_all *all)
{
	int		i;
	int		stop;

	i = 0;
	stop = all->win.nb_row;
	if (all->elem->head)
		stop -= all->win.nb_elem % (all->win.nb_elem / all->win.nb_row);
	while (i < stop)
	{
		if (prev(all) == -1)
			return (-1);
		i++;
	}
	return (0);
}
