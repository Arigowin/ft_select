#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int		next(t_all *all)
{
	char	*res;

	printstr(all->fd, all->elem, all->point.x, all->point.y);
	all->elem->under = FALSE;
	all->elem = all->elem->next;
	if (++(all->point.y) >= all->win.nb_row)
		init_t_point(&(all->point), all->point.x + all->win.col_size, 0);
	else if (all->elem->head)
	{
		init_t_point(&(all->point), 0, 0);
		gohome();
	}
	else
	{
		if ((res = tgetstr("do", NULL)) == NULL)
			return (-1);
		tputs(tgoto(res, all->point.x, all->point.y), 1, my_outc);
	}
	all->elem->under = TRUE;
	if (all->show)
		printstrunder(all->fd, all->elem, all->point.x, all->point.y);
	return (0);
}

int		prev(t_all *all)
{
	char	*res;

	printstr(all->fd, all->elem, all->point.x, all->point.y);
	all->elem->under = FALSE;
	(all->point.y)--;
	if (all->point.y < 0 && all->elem->head == FALSE)
		init_t_point(&(all->point),
				all->point.x - all->win.col_size, all->win.nb_row - 1);
	else if (all->elem->head)
	{
		init_t_point(&(all->point),
				all->win.col_size * (((all->win.nb_elem) - 1) /
					all->win.nb_row),
				((all->win.nb_elem) - 1) % all->win.nb_row);
	}
	else
	{
		if ((res = tgetstr("up", NULL)) == NULL)
			return (-1);
		tputs(tgoto(res, all->point.x, all->point.y), 1, my_outc);
	}
	all->elem->under = TRUE;
	all->elem = all->elem->prev;
	if (all->show)
		printstrunder(all->fd, all->elem, all->point.x, all->point.y);
	return (0);
}

int		del(t_all *all)
{
	t_elements *tmp;

	tmp = all->elem->next;
	all->elem->prev->next = all->elem->next;
	all->elem->next->prev = all->elem->prev;
	if (all->elem->head)
		all->elem->next->head = TRUE;
	free(all->elem->str);
	free(all->elem);
	all->elem = tmp;
	all->elem->under = TRUE;
	while (all->elem->head == FALSE)
		all->elem = all->elem->next;
	(all->win.nb_elem)--;
	if (all->win.nb_elem == 0)
		return (-1);
	clear();
	print_lst(all);
	while (all->elem->under == FALSE)
		all->elem = all->elem->next;
	return (0);
}

int		space(t_all *all)
{
	int		i;

	gobeginogline(all->point.x, all->point.y);
	all->elem->select = !all->elem->select;
	tputs(tgetstr("mr", NULL), 1, my_outc);
	i = 0;
	while (all->elem->str && all->elem->str[i] && i < 47)
	{
		ft_putchar_fd(all->elem->str[i], all->fd);
		i++;
	}
	if (i < (int)ft_strlen(all->elem->str))
		ft_putstr_fd("...", all->fd);
	tputs(tgetstr("me", NULL), 1, my_outc);
	next(all);
	return (0);
}

int		escape(t_all *all)
{
	(void)all;
	return (-1);
}
