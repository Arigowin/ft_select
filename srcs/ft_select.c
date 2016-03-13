#include "ft_select.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int		wintosmal(t_all *all, int i)
{
	if (i == 0)
		ft_putstr_fd("The window size is too small !\n", all->fd);
	return (1);
}

int		lenmax(t_elements **elem)
{
	int			lenmax;
	int			lentmp;
	t_elements	*tmp;

	tmp = *elem;
	lenmax = 0;
	lenmax = ft_strlen(tmp->str);
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->head == FALSE)
	{
		lentmp = ft_strlen(tmp->str);
		if (lentmp > lenmax)
			lenmax = lentmp;
		tmp = tmp->next;
	}
	if (lenmax > 50)
		lenmax = 50;
	return (lenmax + 2);
}

int		ft_select(t_all *all)
{
	t_input		input[7];
	int			ret;

	all->win.col_size = 0;
	all->win.col_size = lenmax(&(all->elem));
	init_t_point(&(all->point), 0, 0);
	init_t_input(input);
	clear();
	gobeginogline(0, 0);
	if (resize(all) == -1)
		wintosmal(all, 0);
	else
		print_lst(all);
	gohome();
	while (1)
	{
		if ((ret = ft_input(input, all)) == -1)
			return (-1);
		else if (ret == -2)
			return (-2);
	}
	return (0);
}
