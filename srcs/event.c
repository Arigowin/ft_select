#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int		next(t_point *point, t_elements **elem, t_win *win)
{
	char	*res;

	printstr((*elem), point->x, point->y);
	(*elem)->under = FALSE;
	(*elem) = (*elem)->next;
	if (++point->y >= win->nb_row)
		init_t_point(point, point->x + win->col_size, 0);
	else if ((*elem)->head)
	{
		init_t_point(point, 0, 0);
		gohome();
	}
	else
	{
		if ((res = tgetstr("do", NULL)) == NULL)
			return (-1);
		tputs(tgoto(res, point->x, point->y), 1, my_outc);
	}
	(*elem)->under = TRUE;
	printstrunder((*elem), point->x, point->y);
	return (0);
}

int		prev(t_point *point, t_elements **elem, t_win *win)
{
	char	*res;

	printstr((*elem), point->x, point->y);
	(*elem)->under = FALSE;
	point->y--;
	if (point->y < 0 && (*elem)->head == FALSE)
		init_t_point(point, point->x - win->col_size, win->nb_row - 1);
	else if ((*elem)->head)
		init_t_point(point, win->col_size * ((win->nb_elem - 1) / win->nb_row),
				(win->nb_elem - 1) % win->nb_row);
	else
	{
		if ((res = tgetstr("up", NULL)) == NULL)
			return (-1);
		tputs(tgoto(res, point->x, point->y), 1, my_outc);
	}
	(*elem)->under = TRUE;
	(*elem) = (*elem)->prev;
	printstrunder((*elem), point->x, point->y);
	return (0);
}


int		escape(t_point *point, t_elements **elem, t_win *win)
{
	(void)point;
	(void)elem;
	(void)win;
	return (-1);
}

int		enter(t_point *point, t_elements **elem, t_win *win)
{
	(void)point;
	(void)win;
	while ((*elem)->head == FALSE)
		*elem = (*elem)->next;
	return (-2);
}

int		del(t_point *point, t_elements **elem, t_win *win)
{
	t_elements *tmp;

	(void)point;
	tmp = (*elem)->next;
	(*elem)->prev->next = (*elem)->next;
	(*elem)->next->prev = (*elem)->prev;
	if ((*elem)->head)
		(*elem)->next->head = TRUE;
	free((*elem)->str);
	free(*elem);
	*elem = tmp;
	(*elem)->under = TRUE;
	while ((*elem)->head == FALSE)
		(*elem) = (*elem)->next;
	win->nb_elem--;
	if (win->nb_elem == 0)
		return (-1);
	print_lst(elem, *win);
	while ((*elem)->under == FALSE)
		(*elem) = (*elem)->next;
	return (0);
}

int		space(t_point *point, t_elements **elem, t_win *win)
{
	gobeginogline(point->x, point->y);
	(*elem)->select = !(*elem)->select;
	if ((*elem)->select)
		ft_putstr_color("\033[0;m", (*elem)->str);
	else
		ft_putstr_color("\033[0;30;47m", (*elem)->str);
	next(point, elem, win);
	return (0);
}
