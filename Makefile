# Executable #
NAME = minishell
# Compile stuff #
CC = gcc
CFGLAGS = -Wall -Werror -Wextra
# Remove #
REMOVE = rm -f
# OBJS #
OBJS = ${SRC:.c=.o}
# LIB #
LIBFT = lib/libft.a
# Source #
SRC = 	./src/main.c \
		./src/check_input.c \
		./src/pipex.c \
		./src/cmds/echo.c \
		./src/cmds/pwd.c \
		./src/cmds/env.c
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

$(NAME): $(OBJS) lib $(LIBFT)
		${CC} ${CFGLAGS} ${OBJS} -L lib -lft -lreadline -o ${NAME}

lib:
	@make -s -C lib

#assert: CFLAGS += -DASSERT=1
#assert: fclean all
#	@python3 ./assert_minishell.py

clean:
	${REMOVE} ${OBJS}

fclean:clean
	${REMOVE} ${NAME}

re: fclean all

run: ${NAME} ${RUN}

.PHONY: all clean fclean re