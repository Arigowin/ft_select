#include "libft.h"
#include "ft_select.h"

int	my_outc(int c)
{
	int		fd;

	fd = 0;
	fd = memoire_fd(fd);
	ft_putchar_fd(c, fd);
	return (0);
}
