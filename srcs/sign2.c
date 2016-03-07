#include "libft.h"
#include "ft_select.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

static void	sigcont(void)
{
	t_all	*all;
	int		fd;

	all = NULL;
	all = memoire(all, 1);
	init_term(all);
	ft_signal();
	fd = memoire_fd(0);
	if (resize(all) == -1)
		ft_putstr_fd("The window size id too small !", fd);
	else
	{
		while (all->elem->head == FALSE)
			all->elem = all->elem->next;
		print_lst(all);
		while (all->elem->under == FALSE)
			all->elem = all->elem->next;
	}
}

static void	sigstop(void)
{
	t_all	*all;
	char	tmp;

	all = NULL;
	all = memoire(all, 1);
	tmp = all->cur_term.c_cc[VSUSP];
	all->cur_term.c_lflag |= (ICANON | ECHO);
	tcsetattr(1, TCSANOW, &(all->cur_term));
	showcursor();
	tputs(tgetstr("te", NULL), 1, my_outc);
	ioctl(1, TIOCSTI, &tmp);
	signal(SIGTSTP, SIG_DFL);
}

static void	sigwinch(void)
{
	t_all	*all;
	int		fd;

	all = NULL;
	all = memoire(all, 1);
	fd = memoire_fd(0);
	if (resize(all) == -1)
		ft_putstr_fd("The window size id too small !", fd);
	else
	{
		while (all->elem->head == FALSE)
			all->elem = all->elem->next;
		print_lst(all);
		while (all->elem->under == FALSE)
			all->elem = all->elem->next;
	}
}

static void	siginter(void)
{
	t_all *all;

	all = NULL;
	all = memoire(all, 1);
	reset_term(all);
	exit(0);
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
