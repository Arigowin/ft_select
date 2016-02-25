#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int	my_outc(int c)
{
	ft_putchar(c);
	return (0);
}

int	printstr(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		my_outc(str[i]);
		i++;
	}
	return (0);
}

int	printstrunder(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str && str[i])
	{
		if ((res = tgetstr("us", NULL)) == NULL)
			return (-1);
		tputs(res, 0, my_outc);
		my_outc(str[i]);
		if ((res = tgetstr("ue", NULL)) == NULL)
			return (-1);
		tputs(res, 0, my_outc);
		i++;
	}
	return (0);
}

int	print_lst(t_elements **elem, int ml)
{
	int	i;
	int	j;
	int	x;
	char	*res;
	t_elements *tmp;

	clear();
	gohome();
	hidecursor();
	i = 1;
	j = 1;
	x = 0;
	tmp = *elem;
	printstrunder(tmp->str);
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->head == FALSE)
	{
		if ((res = tgetstr("cm", NULL)) == NULL)
			return (-1);
		tputs(tgoto(res, x, j), 1, my_outc);
		if (j < ml)
		{
			printstr(tmp->str);
			tmp = tmp->next;
			j++;
		}
		else
		{
			x += 50;
			j = 0;
		}
	}
	my_outc('\n');
	return (0);
}
