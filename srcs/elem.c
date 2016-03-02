#include "ft_select.h"
#include "libft.h"
#include <stdlib.h>

t_elements		*elem_new(char *str)
{
	t_elements	*new;

	if ((new = (t_elements*)malloc(sizeof(t_elements))) == NULL)
		return (NULL);
	if ((new->str = ft_strdup(str)) == NULL)
		return (NULL);
	new->head = FALSE;
	new->under = FALSE;
	new->select = FALSE;
	new->next = NULL;
	new->prev = NULL;
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
