#include "ft_select.h"
#include <stdlib.h>
#include <term.h>
#include <stdio.h>

int		arrows(char buffer[3], int *y, int *x, t_elements **elem, int ac)
{
	char	*res;
	int		ml;

	if ((ml = tgetnum("li")) == -1)
		return (-1);
	if (buffer[0] == 27 && buffer[1] == 91)
	{
		if (buffer[2] == 65)
		{
			gobeginogline(*x, *y);
			printstr((*elem)->str);
			(*elem)->under = FALSE;
			(*y)--;
			if ((*y) < 0 && (*elem)->head == FALSE)
			{
				(*x) -= 50;
				(*y) = ml - 1;
			}
			else
			{
				if ((*elem)->head)
				{
					// si sur le 0 alors aller sur le dernier
					(*x) = 0;
					(*y) = (ac - 2);
					gobeginogline(*x, *y);
				}
				else
				{
					res = tgetstr("up", NULL);
					tputs(tgoto(res, *x, *y), 1, my_outc);
				}
			}
			(*elem) = (*elem)->prev;
			gobeginogline(*x, *y);
			printstrunder((*elem)->str);
			(*elem)->under = TRUE;
		}
		else if (buffer[2] == 66)
		{
			gobeginogline(*x, *y);
			printstr((*elem)->str);
			(*elem)->under = FALSE;
			(*elem) = (*elem)->next;
			(*y)++;
			if ((*y) >= ml)
			{
				(*x) += 50;
				(*y) = 0;
				gobeginogline(*x, *y);
			}
			else
			{
				if ((*elem)->head)
				{
					(*y) = 0;
					(*x) = 0;
					gohome();
				}
				else
				{
					res = tgetstr("do", NULL);
					tputs(tgoto(res, *x, *y), 1, my_outc);
				}
			}
			gobeginogline(*x, *y);
			printstrunder((*elem)->str);
			(*elem)->under = TRUE;
		}
	}
	return (0);
}
