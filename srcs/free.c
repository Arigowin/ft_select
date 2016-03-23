#include "ft_select.h"
#include "libft.h"
#include <stdlib.h>

void	freelst(t_all *all)
{
	t_elements	*tmp;

	while (all->win.nb_elem)
	{
		tmp = all->elem->next;
		all->elem->prev->next = all->elem->next;
		all->elem->next->prev = all->elem->prev;
		free(all->elem->str);
		free(all->elem);
		all->win.nb_elem--;
		all->elem = tmp;
	}
}
