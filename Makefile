NAME	= codexion

CFLAGS	= -Wall -Werror -Wextra -g -Ilibft
CC		= cc


SRCS	=	codexion.c \
			#codex_utils.c \
			#parser.c \


OBJS	= $(SRCS:.c=.o)

.o: .c
	$(CC) $(CFLAGS) -c $(.o) -o $(.c)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)



clean:
	rm -f $(OBJS)

fclean: clean
	cd libft && $(MAKE) fclean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re