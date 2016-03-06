
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

typedef struct			s_input
{
	int					value;
	int					(*fun) (t_point *, t_elements **, t_win *);
}						t_input;

typedef struct			s_all
{
	t_termios			cur_term;
	t_termios			old_term;
	t_elements			*elem;
	t_point				point;
	t_win				win;
}						t_all;

// redesiner que si mis en tache de fond ^z
//				ou suppr
//				ou redimension

int						gobeginogline(int x, int y);
int						my_outc(int c);
int						printstr(t_elements *elem, int x, int y);
int						printstrunder(t_elements *elem, int x, int y);
int						clear(void);
int						gohome(void);
int						hidecursor(void);
int						showcursor(void);
int						print_lst(t_elements **elem, t_win win);
int						next(t_point *point, t_elements **elem, t_win *win);
int						prev(t_point *point, t_elements **elem, t_win *win);
int						escape(t_point *point, t_elements **elem, t_win *win);
int						enter(t_point *point, t_elements **elem, t_win *win);
int						del(t_point *point, t_elements **elem, t_win *win);
int						space(t_point *point, t_elements **elem, t_win *win);
t_elements				*elem_add(t_elements **elem, char *str);
int						init_t_win(t_win *win, int nb_elem);
int						init_t_point(t_point *point, int x, int y);
int						init_t_input(t_input input[7]);
t_bool					init_lst(t_elements **elem, char **av);
int						init_term(t_all *all);
int						print_select(t_elements *elem);

int						reset_term(t_all *all);

int						ft_signal(void);
void					signalhandler(int code);
t_all					*memoire(t_all *all, int code);
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
