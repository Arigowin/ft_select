#include <signal.h>
#include "ft_select.h"

int		ft_signal(void)
{
	int i;
//	signal(SIGCONT, signalhandler);
//	signal(SIGTSTP, signalhandler);
//	signal(SIGWINCH, signalhandler);
//	signal(SIGQUIT, signalhandler);
//	signal(SIGINT, signalhandler);
	i = 1;
	while (i < 32)
	{
		signal(i, signalhandler);
		i++;
	}
	return (1);
}
