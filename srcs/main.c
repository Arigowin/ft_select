#include "ft_select.h"
#include "libft.h"
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char		PC;
extern char		*UP;
extern char		*BC;
extern short	ospeed;

int     body(t_elements **elem, int ac)
{
	char     buffer[3];
	int		ml;
	int		x;
	int		y;
	t_elements *tmp;

	x = 0;
	y = 0;
	if ((ml = tgetnum("li")) == -1)
		return (-1);
	print_lst(elem, ml);
	gohome();
	tmp = *elem;
	while (1)
	{
		read(0, buffer, 3);
		if (arrows(buffer, &y, &x, &tmp, ac) == -1)
			return (-1);
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d, on quitte !\n");
			break ;
		}
	}
	return (0);
}

t_elements		*elem_new(char *str)
{
	t_elements	*new;

	if ((new = (t_elements*)malloc(sizeof(t_elements))) == NULL)
		return (NULL);
	if ((new->str = ft_strdup(str)) == NULL)
		return (NULL);
	new->head = FALSE;
	new->under = FALSE;
	new->next = NULL;
	new->prev = NULL;
	printf("->->%s\n", new->str);
	return (new);
}

t_elements		*elem_add(t_elements **elem, char *str)
{
	t_elements	*tmp;

	if (elem == NULL)
		return (NULL);
	if (*elem == NULL)
	{
		*elem = elem_new(str);
		(*elem)->head = TRUE;
		(*elem)->under = TRUE;
	}
	else
	{
		tmp = *elem;
		while (tmp->next && tmp->next->head == FALSE)
			tmp = tmp->next;
		tmp->next = elem_new(str);
		tmp->next->prev = tmp;
		(*elem)->prev = tmp->next;
		tmp->next->next = *elem;
		return (tmp->next);
	}
	return (*elem);
}

t_bool		init_lst(t_elements **elem, char **av)
{
	int		i;

	i = 1;
	while(av[i])
	{
		if (elem_add(elem, av[i]) == NULL)
			return (FALSE);
		i++;
	}
	(*elem)->under = TRUE;
	return (TRUE);
}

int              main(int ac, char **av)
{
	char			*name_term;
	struct termios	term;
	struct termios	term_old;
	t_elements		*elem;
//	t_elements		*tmp;

	elem = NULL;
	if (ac > 1)
	{
		if (init_lst(&elem, av) == FALSE)
			return (-1);
//		tmp = elem;
//		printf("%s\n", tmp->str);
//		tmp = tmp->next;
//		while(tmp->head == FALSE)
//		{
//			printf("%s\n", tmp->str);
//			tmp = tmp->next;
//		}
		if ((name_term = getenv("TERM")) == NULL)
			return (-1);
		if (tgetent(NULL, name_term) == -1)
			return (-1);
		// remplis la structure termios des possibilités du terminal.
		if (tcgetattr(0, &term) == -1)
			return (-1);
		if (tcgetattr(0, &term_old) == -1)
			return (-1);
		term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
		term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		// On applique les changements :
		if (tcsetattr(0, TCSADRAIN, &term) == -1)
			return (-1);
		body(&elem, ac);

		clear();
		showcursor();

		if (tcsetattr(0, TCSANOW, &term_old) == -1)
			return (-1);
	}
	return (0);
}
