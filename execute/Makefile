CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

LIBFT = ../libft/libft.a
LIBFT_DIR = ../libft/

SRCS = execution_test.c execute.c execute_command.c execute_redir.c execute_utils.c \
		execute_pipe.c get_next_line.c get_next_line_utils.c execute_builtin.c \
		builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c builtin_export.c builtin_pwd.c builtin_unset.c envp_utils.c
SRCS_OBJS = $(SRCS:.c=.o)

LDFLAGS = -lreadline -lhistory -L$(READ_DIR)
INCLUDES = -I$(READ_HDRS)
READ_DIR = ./readline/lib/
READ_HDRS	= ./readline/include/

OBJS = $(SRCS_OBJS)

all : $(NAME)

$(NAME) : rl $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(LDFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJS)
	rm -rf rlsrc
	rm -f *.txt heredoc_tmp*

fclean : clean
	rm -f $(NAME)
	rm -rf readline
	rm -f rl

re : fclean all

rl :
	git clone git://git.savannah.gnu.org/readline.git rlsrc
	cd rlsrc && ./configure --prefix="${PWD}/readline"
	$(MAKE) --directory=rlsrc
	$(MAKE) --directory=rlsrc install
	touch rl

.PHONY : clean fclean re