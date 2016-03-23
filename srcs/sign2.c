/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:17 by dolewski          #+#    #+#             */
/*   Updated: 2016/03/23 12:05:17 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

static void	sigstop(void)
{
	t_all	*all;
	int		fd;

	all = NULL;
	all = memoire(all, 1);
	fd = memoire_fd(0);
	all->cur_term.c_lflag |= (ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &(all->cur_term));
	showcursor();
	tputs(tgetstr("te", NULL), 1, my_outc);
	ioctl(STDOUT_FILENO, TIOCSTI, "\032");
	signal(SIGTSTP, SIG_DFL);
}

static void	siginter(void)
{
	t_all *all;

	all = NULL;
	all = memoire(all, 1);
	reset_term(all);
	exit(0);
}

static void	sigcont(void)
{
	t_all	*all;

	all = NULL;
	all = memoire(all, 1);
	init_term(all);
	ft_signal();
	if (resize(all) == -1)
		wintosmal(all, 0);
	else
	{
		while (all->elem->head == FALSE)
			all->elem = all->elem->next;
		print_lst(all);
		while (all->elem->under == FALSE)
			all->elem = all->elem->next;
	}
}

static void	sigwinch(void)
{
	t_all	*all;

	all = NULL;
	all = memoire(all, 1);
	if (resize(all) == -1)
		wintosmal(all, 0);
	else
	{
		while (all->elem->head == FALSE)
			all->elem = all->elem->next;
		print_lst(all);
		while (all->elem->under == FALSE)
			all->elem = all->elem->next;
	}
}

void		signalhandler(int code)
{
	if (code == SIGCONT)
		sigcont();
	else if (code == SIGTSTP)
		sigstop();
	else if (code == SIGWINCH)
		sigwinch();
	else if (code == SIGQUIT || code == SIGINT)
		siginter();
}
