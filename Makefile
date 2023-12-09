# Specify the libraries to be built
LIBFT = libft/libft.a

SRC = pipex.c utils.c utils2.c
OBJS = $(SRC:.c=.o)

CC = cc
RM = rm -f
# CFLAGS = -Wall -Werror -Wextra
NAME = pipex

all: $(LIBFT) ${NAME}

$(LIBFT):
	@make -C libft

${NAME}: $(LIBFT) ${OBJS}
	$(CC) $(CFLAGS) -o ${NAME} ${OBJS} -Llibft -lft

$(OBJS): $(SRC) libft/libft.h
	$(CC) $(CFLAGS) -c $(SRC) -Ilibft

clean:
	@make -C libft clean
	$(RM) ${OBJS}

fclean: clean
	@make -C libft fclean
	$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re
