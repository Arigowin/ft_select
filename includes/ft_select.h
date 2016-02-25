
#ifndef FT_SELECT_H
# define FT_SELECT_H
# define TRUE 1
# define FALSE 0

typedef char			t_bool;

typedef struct			s_elements
{
	char				*str;
	t_bool				under;
	t_bool				head;
	struct s_elements	*next;
	struct s_elements	*prev;
}						t_elements;

// ajout de structure doublement chainer avec position du curseur dedant
// redesiner que si mis en tache de fond ^z
//				ou suppr
//				ou redimension

int						gobeginogline(int x, int y);
int						my_outc(int c);
int						printstr(char *str);
int						printstrunder(char *str);
int						arrows(char buffer[3], int *y, int *x, t_elements **elem, int ac);
int						clear(void);
int						gohome(void);
int						hidecursor(void);
int						showcursor(void);
int						print_lst(t_elements **elem, int ml);

#endif

/*
** - unistd.h
**		isatty
**		ttyname
**		ttyslot
**		tcsetattr
**		tcgetattr
**		close
**		write
**		read
** - stdlib.h
**		ttyslot
**		getenv
**		malloc
** 		free
**		exit
** - sys/ioctl.h
**		ioctl
**	- termios.h
**		tcsetattr
**		tcgetattr
** - curses.h
**		tgetent
**		tgetflag
**		tgetnum
**		tgetstr
**		tgoto
**		tputs
** - term.h
**		tgetent
**		tgetflag
**		tgetnum
**		tgetstr
**		tgoto
**		tputs
** - fcntl.h
**		open
** - signal.h
**		signal
*/
