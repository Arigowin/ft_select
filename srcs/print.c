#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int	my_outc(int c)
{
	ft_putchar(c);
	return (0);
}

int	printstr(t_elements *elem, int x, int y)
{
	gobeginogline(x, y);
	if (elem->select)
		ft_putstr_color("\033[30;47m", elem->str);
	else
		ft_putstr_color("\033[0;m", elem->str);
	return (0);
}

int	printstrunder(t_elements *elem, int x, int y)
{
	char	*res;
	int		i;

	i = 0;
	gobeginogline(x, y);
	while (elem->str && elem->str[i])
	{
		if ((res = tgetstr("us", NULL)) == NULL)
			return (-1);
		tputs(res, 0, my_outc);
		if (elem->select)
			ft_putchar_color("\033[30;47m", elem->str[i]);
		else
			ft_putchar(elem->str[i]);
		if ((res = tgetstr("ue", NULL)) == NULL)
			return (-1);
		tputs(res, 0, my_outc);
		i++;
	}
	return (0);
}

int	print_one_elem(t_elements **elem, t_win win, int *j, int *x)
{
	char	*res;

	if ((res = tgetstr("cm", NULL)) == NULL)
		return (-1);
	tputs(tgoto(res, *x, *j), 1, my_outc);
	if (*j < win.nb_row)
	{
		if ((*elem)->under)
			printstrunder(*elem, *x, *j);
		else
			printstr(*elem, *x, *j);
		(*elem) = (*elem)->next;
		(*j)++;
	}
	else
	{
		*x += win.col_size;
		(*j) = 0;
	}
	return (1);
}

int	print_lst(t_elements **elem, t_win win)
{
	t_elements	*tmp;
	int			j;
	int			x;

	clear();
	gohome();
	hidecursor();
	x = 0;
	j = 1;
	tmp = *elem;
	if (tmp->under)
		printstrunder(*elem, 0, 0);
	else
		printstr(*elem, 0, 0);
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->head == FALSE)
	{
		if (print_one_elem(&tmp, win, &j, &x) == -1)
			return (-1);
	}
	my_outc('\n');
	return (0);
}
