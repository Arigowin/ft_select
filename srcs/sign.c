#include "ft_select.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

void	sigcont(void)
{
	t_all *all;

	all = NULL;
	all = memoire(all, 1);
	init_term(all);
	ft_signal();
	resize(all);
	while (all->elem->head == FALSE)
		all->elem = all->elem->next;
	print_lst(&(all->elem), all->win);
	while (all->elem->under == FALSE)
		all->elem = all->elem->next;
}

void	sigstop(void)
{
	t_all	*all;
	char	tmp;

	all = NULL;
	all = memoire(all, 1);
	tmp = all->cur_term.c_cc[VSUSP];
	all->cur_term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &(all->cur_term));
	showcursor();
	tputs(tgetstr("te", NULL), 1, my_outc);
	ioctl(0, TIOCSTI, &tmp);
	signal(SIGTSTP, SIG_DFL);
}

void	sigwinch(void)
{
	t_all	*all;

	all = NULL;
	all = memoire(all, 1);
	resize(all);
	while (all->elem->head == FALSE)
		all->elem = all->elem->next;
	print_lst(&(all->elem), all->win);
	while (all->elem->under == FALSE)
		all->elem = all->elem->next;
}

void	siginter(void)
{
	t_all *all;

	all = NULL;
	all = memoire(all, 1);
	reset_term(all);
	exit(0);
}

void	signalhandler(int code)
{
	if (code == SIGCONT)
		sigcont();
	else if (code == SIGTSTP)
		sigstop();
	else if (code == SIGWINCH)
		sigwinch();
	else
		siginter();
}

int		ft_signal(void)
{
	int		i;

	i = 1;
	// enlever catch all signal
//	signal(SIGCONT, signalhandler);
//	signal(SIGTSTP, signalhandler);
//	signal(SIGWINCH, signalhandler);
//	signal(SIGQUIT, signalhandler);
	while (i < 32)
	{
		signal(i, signalhandler);
		i++;
	}
	return (1);
}


/*
 * 1     SIGHUP       terminate process    terminal line hangup
 * 2     SIGINT       terminate process    interrupt program
 * 3     SIGQUIT      create core image    quit program
 * 4     SIGILL       create core image    illegal instruction
 * 5     SIGTRAP      create core image    trace trap
 * 6     SIGABRT      create core image    abort program (formerly SIGIOT)
 * 7     SIGEMT       create core image    emulate instruction executed
 * 8     SIGFPE       create core image    floating-point exception
 * 9     SIGKILL      terminate process    kill program
 * 10    SIGBUS       create core image    bus error
 * 11    SIGSEGV      create core image    segmentation violation
 * 12    SIGSYS       create core image    non-existent system call invoked
 * 13    SIGPIPE      terminate process    write on a pipe with no reader
 * 14    SIGALRM      terminate process    real-time timer expired
 * 15    SIGTERM      terminate process    software termination signal
 * 16    SIGURG       discard signal       urgent condition present on socket
 * 17    SIGSTOP      stop process         stop (cannot be caught or ignored)
 * 18    SIGTSTP      stop process         stop signal generated from keyboard
 * 19    SIGCONT      discard signal       continue after stop
 * 20    SIGCHLD      discard signal       child status has changed
 * 21    SIGTTIN      stop process         background read attempted from control terminal
 * 22    SIGTTOU      stop process         background write attempted to control terminal
 * 23    SIGIO        discard signal       I/O is possible on a descriptor (see fcntl(2))
 * 24    SIGXCPU      terminate process    cpu time limit exceeded (see setrlimit(2))
 * 25    SIGXFSZ      terminate process    file size limit exceeded (see setrlimit(2))
 * 26    SIGVTALRM    terminate process    virtual time alarm (see setitimer(2))
 * 27    SIGPROF      terminate process    profiling timer alarm (see setitimer(2))
 * 28    SIGWINCH     discard signal       Window size change
 * 29    SIGINFO      discard signal       status request from keyboard
 * 30    SIGUSR1      terminate process    User defined signal 1
 * 31    SIGUSR2      terminate process    User defined signal 2
 */
