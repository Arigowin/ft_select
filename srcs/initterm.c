#include "ft_select.h"
#include "libft.h"
#include <term.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static int	init_term_2(t_all *all)
{
	char	*tmp;

	tmp = ttyname(0);
	if ((all->fd = open(tmp, O_NOCTTY | O_WRONLY)) == -1)
		return (-1);
	memoire_fd(all->fd);
	if ((tmp = getenv("TERM")) == NULL)
		tmp = "xterm-256color";
	if (tgetent(NULL, tmp) == -1)
		return (-1);
	return (1);
}

int			init_term(t_all *all)
{
	char	*res;

	all->fd = 0;
	init_term_2(all);
	if (tcgetattr(all->fd, &(all->cur_term)) == -1)
		return (-1);
	if (tcgetattr(all->fd, &(all->old_term)) == -1)
		return (-1);
	all->cur_term.c_lflag &= ~(ICANON | ECHO);
	all->cur_term.c_cc[VMIN] = 1;
	all->cur_term.c_cc[VTIME] = 0;
	if (tcsetattr(all->fd, TCSADRAIN, &(all->cur_term)) == -1)
		return (-1);
	if ((res = tgetstr("ti", NULL)) == NULL)
		return (-1);
	tputs(res, 1, my_outc);
	hidecursor();
	return (0);
}

