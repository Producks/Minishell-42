# Executable #
NAME = minishell
# Compile stuff #
CC = @gcc
CFGLAGS = -Wall -Werror -Wextra
# Remove #
REMOVE = @rm -f
# OBJS #
OBJS = ${SRC:.c=.o}
# LIB #
LIBFT = lib/libft.a
# RUN #
RUN = @./minishell
# Source #
SRC = 	./src/main.c\
		./src/execution/pipex.c\
		./src/cmds/echo.c\
		./src/cmds/pwd.c\
		./src/cmds/env.c\
		./src/cmds/cd.c\
		./src/cmds/export.c\
		./src/cmds/ft_exit.c\
		./src/cmds/unset.c\
		./src/init.c \
		./src/parsing/check_input.c
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
		${CC} ${CFGLAGS} ${OBJS} -L lib -lft -lreadline -o ${NAME}
	@echo "$(GREEN)Done$(WHITE)"

lib:
	@make -s -C lib

#assert: CFLAGS += -DASSERT=1
#assert: fclean all
#	@python3 ./assert_minishell.py

clean:
	@make clean -s -C lib
	${REMOVE} ${OBJS}

fclean:clean
	@make fclean -s -C lib
	${REMOVE} ${NAME}
	@echo "$(RED)Cleaning done$(WHITE)"

re: fclean all

run: all
	${RUN}

.PHONY: all clean fclean re lib run