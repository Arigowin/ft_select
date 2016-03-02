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

int		ft_input(t_input input[7], t_point *point, t_win *win, t_elements **tmp)
{
	int			buf;
	int			i;

	buf = 0;
	if (read(0, (char *)&buf, 3) == -1)
		return (-1);
	i = 0;
	while (i < 7 && buf != (input[i]).value)
		i++;
	if (i < 7 && buf == (input[i]).value)
	{
		if ((input[i]).fun(point, tmp, win) == -1)
			return (-1);
	}
	return (0);
}

int     ft_select(t_elements **elem, int ac)
{
	t_input		input[7];
	t_point		point;
	t_win		win;
	t_elements	*tmp;

	init_t_win(&win, ac - 1);
	win.col_size = lenmax(elem);
	init_t_point(&point, 0, 0);
	print_lst(elem, win);
	gohome();
	init_t_input(input);
	tmp = *elem;
	if (signal(SIGWINCH, signalhandler) == ((void (*)(/*int*/))SIGWINCH))
	{
		printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		print_lst(elem, win);
	}
	while (1)
	{
		if (ft_input(input, &point, &win, &tmp) == -1)
			return (-1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	struct termios	term;
	struct termios	term_old;
	t_elements		*elem;

	elem = NULL;
	if (ac > 1)
	{
		signal(SIGINT, signalhandler);
		signal(SIGCONT, signalhandler);
		init_term(&term, &term_old, av, &elem);
		ft_select(&elem, ac);

		clear();
		showcursor();

		if (tcsetattr(0, TCSANOW, &term_old) == -1)
			return (-1);
	}
	return (0);
}
