CC =	/usr/bin/clang
RM =	/bin/rm
MAKE =	/usr/bin/make
MKDIR =	/bin/mkdir

NAME = ft_select

ROOT =		$(shell /bin/pwd)
OPATH =		$(ROOT)/objs
CPATH =		$(ROOT)/srcs
HPATH =		$(ROOT)/includes
LIBPATH =	$(ROOT)/libft
LIBHPATH =	$(LIBPATH)/includes

CFLAGS = -O3 -Wall -Werror -Wextra -I $(HPATH) -I $(LIBHPATH)
LIBS = -L $(LIBPATH) -lft -ltermcap

SRC = elem.c \
	event.c \
	event2.c \
	free.c \
	ft_select.c \
	iniscreen.c \
	init.c \
	initterm.c \
	input.c \
	main.c \
	mem.c \
	move.c \
	print.c \
	sign.c \
	sign2.c \
	tputs.c

OFILES = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

.PHONY: all clean fclean re lib.fclean

all: $(OPATH) $(NAME)

$(NAME): $(OFILES)
	@echo "$(NAME) : Building Libft"
	@$(MAKE) -C $(LIBPATH)
	@echo "$(NAME) : Building $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\033[32mDone !\033[0m"

$(OPATH)/%.o: $(CPATH)/%.c
	@echo "$(NAME) : Creating file $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OPATH):
	@echo "$(NAME) : Creating objs directory"
	@$(MKDIR) $@

clean:
	@echo "$(NAME) : Deleting objs"
	@$(RM) -rf $(OPATH)

fclean: clean lib.fclean
	@echo "$(NAME) : Deleting $(NAME)"
	@$(RM) -f $(NAME)
	@echo "\033[32mDone !\033[0m"

lib.fclean:
	@$(MAKE) fclean -C $(LIBPATH)

re: fclean all
