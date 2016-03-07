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
