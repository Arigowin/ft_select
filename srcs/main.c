#include "ft_select.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_all			all;
	int				ret;

	all.elem = NULL;
	if (ac > 1)
	{
		ft_signal();
		if (init_term(&all))
			return (-1);
		if (init_lst(&(all.elem), av) == FALSE)
			return (-1);
		all.win.nb_elem = ac - 1;
		memoire(&all, 0);
		ret = ft_select(&all);
		if (reset_term(&all) == -1)
			return (-1);
		if (ret == -2)
			print_select(&all);
	}
	return (0);
}
