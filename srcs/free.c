#include "ft_select.h"
#include "libft.h"
#include <stdlib.h>

void	freelst(t_elements **elem)
{
	t_elements	*tmp;

	while (elem && *elem && (*elem)->next)
	{
		tmp = (*elem)->next;
		(*elem)->prev->next = NULL;
		ft_strdel(&((*elem)->str));
		free(*elem);
		*elem = tmp;
	}
}
