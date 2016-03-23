/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:16 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:16 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int	printstr(int fd, t_elements *elem, int x, int y)
{
	int		i;

	gobeginogline(x, y);
	i = 0;
	if (elem->select)
		tputs(tgetstr("mr", NULL), 1, my_outc);
	while (elem->str && elem->str[i] && i < 47)
	{
		ft_putchar_fd(elem->str[i], fd);
		i++;
	}
	if (i < (int)ft_strlen(elem->str))
		ft_putstr_fd("...", fd);
	tputs(tgetstr("me", NULL), 1, my_outc);
	return (0);
}

int	printstrunder(int fd, t_elements *elem, int x, int y)
{
	int		i;

	i = 0;
	gobeginogline(x, y);
	while (elem->str && elem->str[i] && i < 47)
	{
		tputs(tgetstr("us", NULL), 1, my_outc);
		if (elem->select)
			ft_putchar_color_fd(fd, "\033[45m", elem->str[i]);
		else
			ft_putchar_color_fd(fd, "\033[41m", elem->str[i]);
		i++;
	}
	tputs(tgetstr("us", NULL), 1, my_outc);
	if (i < (int)ft_strlen(elem->str))
		ft_putstr_fd("...", fd);
	tputs(tgetstr("ue", NULL), 2, my_outc);
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
