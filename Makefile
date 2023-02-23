# Executable #
NAME = minishell
# Compile stuff #
CC = gcc
CFGLAGS = -Wall -Werror -Wextra
# Remove #
REMOVE = rm -f
# OBJS #
OBJS = ${SRC:.c=.o}
#LIB #
LIBFT = lib/Libft-42/libft.a
# Source #
SRC = 	./src/main.c \
		./src/check_input.c \
		./src/pipex.c
# Colors #
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m


all: lib $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		${CC} ${CFGLAGS} ${OBJS} -L lib/Libft-42/ -lft -lreadline -o ${NAME}

lib:
	@make -s -C libs/Libft-42

clean:
	${REMOVE} ${OBJS}

fclean:clean
	${REMOVE} ${NAME}

re: fclean all

run: ${NAME} ${RUN}

.PHONY: all clean fclean re