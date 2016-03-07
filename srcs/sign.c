#include <signal.h>
#include "ft_select.h"

int		ft_signal(void)
{
	signal(SIGCONT, signalhandler);
	signal(SIGTSTP, signalhandler);
	signal(SIGWINCH, signalhandler);
	signal(SIGQUIT, signalhandler);
	signal(SIGINT, signalhandler);
	return (1);
}
