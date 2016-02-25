#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

int		gobeginogline(int x, int y)
{
	char	*res;

	if ((res = tgetstr("cm", NULL)) == NULL)
		return (-1);
	tputs(tgoto(res, x, y), 0, my_outc);
	return (0);
}
