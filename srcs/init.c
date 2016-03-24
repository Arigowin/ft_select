/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:15 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/24 15:41:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <stdlib.h>

int			init_t_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
	return (0);
}

int			init_t_input(t_input input[9])
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
	(input[7]).value = 4414235;
	(input[7]).fun = &right;
	(input[8]).value = 4479771;
	(input[8]).fun = &left;
	return (0);
}

t_bool		init_lst(t_elements **elem, char **av, t_all *all)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] != '\0')
		{
			if (elem_add(elem, av[i]) == NULL)
				return (FALSE);
			all->win.nb_elem++;
		}
		i++;
	}
	if (all->win.nb_elem == 0)
		return (FALSE);
	return (TRUE);
}

int			reset_term(t_all *all)
{
	showcursor();
	all->old_term.c_lflag |= (ICANON | ECHO);
	tputs(tgetstr("te", NULL), 1, my_outc);
	if (tcsetattr(all->fd, TCSANOW, &(all->old_term)) == -1)
		return (-1);
	return (0);
}
