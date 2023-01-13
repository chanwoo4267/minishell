CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

LIBFT = ../libft/libft.a
LIBFT_DIR = ../libft/

SRCS = execution_test.c execute.c execute_command.c execute_redir.c execute_utils.c
SRCS_OBJS = $(SRCS:.c=.o)

GNL_NAME = get_next_line.c get_next_line_utils.c
GNL_OBJS = $(GNL_NAME:.c=.o)

OBJS = $(SRCS_OBJS) $(GNL_OBJS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJS)
	rm -f *.txt

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re