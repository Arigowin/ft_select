#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int	printstr(int fd, t_elements *elem, int x, int y)
{
	gobeginogline(x, y);
	if (elem->select)
	{
		tputs(tgetstr("mr", NULL), 1, my_outc);
		ft_putstr_fd(elem->str, fd);
		tputs(tgetstr("me", NULL), 1, my_outc);
	}
	else
		ft_putstr_fd(elem->str, fd);
	return (0);
}

int	printstrunder(int fd, t_elements *elem, int x, int y)
{
	char	*res;
	int		i;

	i = 0;
	gobeginogline(x, y);
	while (elem->str && elem->str[i])
	{
		if ((res = tgetstr("us", NULL)) == NULL)
			return (-1);
		tputs(res, 1, my_outc);
		if (elem->select)
		{
			tputs(tgetstr("mr", NULL), 1, my_outc);
			ft_putchar_fd(elem->str[i], fd);
			tputs(tgetstr("me", NULL), 1, my_outc);
		}
		else
			ft_putchar_fd(elem->str[i], fd);
		if ((res = tgetstr("ue", NULL)) == NULL)
			return (-1);
		tputs(res, 1, my_outc);
		i++;
	}
	return (0);
}

int	print_one_elem(t_all *all, t_elements **elem, int *j, int *x)
{
	char	*res;

	if ((res = tgetstr("cm", NULL)) == NULL)
		return (-1);
	tputs(tgoto(res, *x, *j), 1, my_outc);
	if (*j < all->win.nb_row)
	{
		if ((*elem)->under)
			printstrunder(all->fd, *elem, *x, *j);
		else
			printstr(all->fd, *elem, *x, *j);
		(*elem) = (*elem)->next;
		(*j)++;
	}
	else
	{
		*x += all->win.col_size;
		(*j) = 0;
	}
	return (1);
}

int	print_lst(t_all *all)
{
	t_elements	*tmp;
	int			j;
	int			x;

	gohome();
	x = 0;
	j = 1;
	tmp = all->elem;
	if (tmp->under)
		printstrunder(all->fd, tmp, 0, 0);
	else
		printstr(all->fd, tmp, 0, 0);
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->head == FALSE)
	{
		if (print_one_elem(all, &tmp, &j, &x) == -1)
			return (-1);
	}
	my_outc('\n');
	return (0);
}

int	print_select(t_all *all)
{
	if (all->elem->select)
	{
		ft_putstr_fd(all->elem->str, 1);
		ft_putstr_fd(" ", 1);
	}
	all->elem = all->elem->next;
	while (all->elem && all->elem->next && all->elem->head == FALSE)
	{
		if (all->elem->select)
		{
			ft_putstr_fd(all->elem->str, 1);
			ft_putstr_fd(" ", 1);
		}
		all->elem = all->elem->next;
	}
	return (0);
}
