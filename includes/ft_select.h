
#ifndef FT_SELECT_H
# define FT_SELECT_H
# define TRUE 1
# define FALSE 0

#include <term.h>
typedef char			t_bool;
typedef struct termios	t_termios;

typedef struct			s_elements
{
	char				*str;
	t_bool				select;
	t_bool				head;
	t_bool				under;
	struct s_elements	*next;
	struct s_elements	*prev;
}						t_elements;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_win
{
	int					nb_col;
	int					nb_row;
	int					col_size;
	int					nb_elem;
}						t_win;

typedef struct			s_all
{
	t_termios			cur_term;
	t_termios			old_term;
	t_elements			*elem;
	t_point				point;
	t_win				win;
	int					fd;
}						t_all;

typedef struct			s_input
{
	int					value;
	int					(*fun) (t_all *);
}						t_input;

// redesiner que si mis en tache de fond ^z
//				ou suppr
//				ou redimension

int						gobeginogline(int x, int y);

int						clear(void);
int						gohome(void);
int						hidecursor(void);
int						showcursor(void);

int						next(t_all *all);
int						prev(t_all *all);
int						escape(t_all *all);
int						enter(t_all *all);
int						del(t_all *all);
int						space(t_all *all);

t_elements				*elem_add(t_elements **elem, char *str);

int						init_t_point(t_point *point, int x, int y);
int						init_t_input(t_input input[7]);
t_bool					init_lst(t_elements **elem, char **av);
int						init_term(t_all *all);

int						my_outc(int c);
int						printstr(int fd, t_elements *elem, int x, int y);
int						printstrunder(int fd, t_elements *elem, int x, int y);
int						print_lst(t_all *all);
int						print_select(t_all *all);

int						reset_term(t_all *all);

int						ft_signal(void);
void					signalhandler(int code);

t_all					*memoire(t_all *all, int code);
int						memoire_fd(int fd);

void					resize(t_all *all);

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
