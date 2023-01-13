SRCS = test.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
LDFLAGS = -lreadline -lhistory -L$(READ_DIR)
INCLUDES = -I$(READ_HDRS)
READ_DIR = ./readline/lib/
READ_HDRS	= ./readline/include/

all : $(NAME)

$(NAME) : $(OBJS) rl
	cc -Wall -Wextra -Werror $(LDFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o : %.c
	cc -Wall -Wextra -Werror -c $<

clean :
	rm -f $(OBJS)
	rm -rf rlsrc

fclean : clean
	rm -f $(NAME)
	rm -rf readline rl

re : fclean all

rl :
	git clone git://git.savannah.gnu.org/readline.git rlsrc
	cd rlsrc && ./configure --prefix="${PWD}/readline"
	$(MAKE) --directory=rlsrc
	$(MAKE) --directory=rlsrc install
	touch rl

.PHONY : clean fclean re