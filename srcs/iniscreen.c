#include "ft_select.h"
#include <stdlib.h>
#include <term.h>
#include <sys/ioctl.h>

int		clear(void)
{
	char	*res;

	if ((res = tgetstr("cl", NULL)) == NULL)
		return (-1);
	tputs(res, 1, my_outc);
	return (0);
}

int		gohome(void)
{
	char	*res;

	if ((res = tgetstr("ho", NULL)) == NULL)
		return (-1);
	tputs(tgoto(res, 0, 0), 1, my_outc);
	return (0);
}

int		hidecursor(void)
{
	char	*res;

	if ((res = tgetstr("vi", NULL)) == NULL)
		return (-1);
	tputs(res, 1, my_outc);
	return (0);
}

int		showcursor(void)
{
	char	*res;

	if ((res = tgetstr("ve", NULL)) == NULL)
		return (-1);
	tputs(res, 1, my_outc);
	if ((res = tgetstr("vs", NULL)) == NULL)
		return (-1);
	tputs(res, 1, my_outc);
	return (0);
}

int		resize(t_all *all)
{
	struct winsize	win;

	clear();
	ioctl(all->fd, TIOCGWINSZ, &win);
	all->win.nb_col = win.ws_col;
	all->win.nb_row = win.ws_row;
	if ((((all->win.nb_elem / all->win.nb_row) * all->win.col_size) - 1
				> all->win.nb_col) || all->win.nb_row < 4)
		return (-1);
	return (1);
}
