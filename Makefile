NAME	= codexion

CFLAGS	= -Wall -Werror -Wextra -pthread
CC		= cc


SRCS	=	codexion.c \
			parser.c \
			rotine.c \
			codex_utils.c \


OBJS	= $(SRCS:.c=.o)

.o: .c
	$(CC) $(CFLAGS) -c $(.o) -o $(.c)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)



clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re