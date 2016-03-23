/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:16 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:16 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_all			all;
	int				ret;

	all.elem = NULL;
	all.win.nb_elem = 0;
	all.show = 1;
	if (ac > 1 && av[0] != NULL && av[1] != NULL && av[1][0] != '\0')
	{
		ft_signal();
		if (init_term(&all))
			return (-1);
		if (init_lst(&(all.elem), av, &all) == FALSE)
			return (-1);
		memoire(&all, 0);
		ret = ft_select(&all);
		if (reset_term(&all) == -1)
			return (-1);
		if (ret == -2)
			print_select(&all);
		if (all.win.nb_elem > 0)
			freelst(&all);
	}
	return (0);
}
