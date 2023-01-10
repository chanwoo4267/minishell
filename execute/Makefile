CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

LIBFT = ../libft/libft.a
LIBFT_DIR = ../libft/

SRCS = execution_test.c execution.c redirection.c
OBJS = $(SRCS:.c=.o)

GNL_NAME = get_next_line.c get_next_line_utils.c
GNL_DIRS = ../get_next_line/
GNL_SRCS = $(addprefix $(GNL_DIRS), $(GNL_NAME))
GNL_OBJS = $(GNL_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(GNL_OBJS)
	make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	make clean -C $(LIBFT_DIR)
	rm -f $(GNL_OBJS) $(OBJS)

fclean : clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re