#include "ft_select.h"
#include <term.h>
#include <stdlib.h>
#include <stdio.h>

int		init_t_win(t_win *win, int nb_elem)
{
	int		r;
	int		c;

	r = win->nb_row;
	c = win->nb_col;
	if ((win->nb_row = tgetnum("li")) == -1)
		return (-1);
	if ((win->nb_col = tgetnum("co")) == -1)
		return (-1);
	win->nb_elem = nb_elem;
	win->col_size = 0;
	if (win->nb_col != c || win->nb_row != r)
		return (1);
	return (0);
}

int		init_t_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
	return (0);
}

int		init_t_input(t_input input[7])
{
	(input[0]).value = 4283163;
	(input[0]).fun = &prev;
	(input[1]).value = 4348699;
	(input[1]).fun = &next;
	(input[2]).value = 27;
	(input[2]).fun = &escape;
	(input[3]).value = 10;
	(input[3]).fun = &enter;
	(input[4]).value = 3365659;
	(input[4]).fun = &del;
	(input[5]).value = 127;
	(input[5]).fun = &del;
	(input[6]).value = 32;
	(input[6]).fun = &space;
	return (0);
}

t_bool		init_lst(t_elements **elem, char **av)
{
	int		i;

	i = 1;
	while(av[i])
	{
		if (elem_add(elem, av[i]) == NULL)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		init_term(t_all *all)
{
	char	*res;

	if (tgetent(NULL, getenv("TERM")) == -1)
		return (-1);
	if (tcgetattr(0, &(all->cur_term)) == -1)
		return (-1);
	if (tcgetattr(0, &(all->old_term)) == -1)
		return (-1);
	all->cur_term.c_lflag &= ~(ICANON | ECHO);
	all->cur_term.c_cc[VMIN] = 1;
	all->cur_term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &(all->cur_term)) == -1)
		return (-1);
	if ((res = tgetstr("ti", NULL)) == NULL)
		return (-1);
	tputs(res, 0, my_outc);
	hidecursor();
	return (0);
}

int		reset_term(t_all *all)
{
	clear();
	showcursor();
	if (tcsetattr(0, TCSANOW, &(all->old_term)) == -1)
		return (-1);
	return (0);
}
