#include "ft_select.h"
#include "libft.h"
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

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
	return (lenmax + 2);
}

int		ft_input(t_input input[7], t_point *point, t_elements **tmp, t_win *win)
{
	int			buf;
	int			i;
	int			ret;

	buf = 0;
	if (read(0, (char *)&buf, 3) == -1)
		return (-1);
	i = 0;
	while (i < 7 && buf != (input[i]).value)
		i++;
	if (i < 7 && buf == (input[i]).value)
	{
		if ((ret = (input[i]).fun(point, tmp, win)) == -1)
			return (-1);
		else if (ret == -2)
			return (-2);
	}
	return (0);
}

int     ft_select(t_all *all, int ac)
{
	t_input		input[7];
	int			ret;

	init_t_win(&(all->win), ac - 1);
	all->win.col_size = lenmax(&(all->elem));
	init_t_point(&(all->point), 0, 0);
	init_t_input(input);
	clear();
	print_lst(&(all->elem), (all->win));
	gohome();
	while (1)
	{
		if ((ret = ft_input(input, &all->point, &(all->elem), &all->win)) == -1)
			return (-1);
		else if (ret == -2)
			return (-2);
	}
	return (0);
}

t_all	*memoire(t_all *all, int code)
{
	static t_all *tmp;

	if (code == 0)
		tmp = all;
	return (tmp);
}

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
		memoire(&all, 0);
		ret = ft_select(&all, ac);
		if (reset_term(&all) == -1)
			return (-1);
		if (ret == -2)
			print_select(all.elem);
	}
	return (0);
}
