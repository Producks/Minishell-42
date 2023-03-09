# Executable #
NAME = minishell
# Compile stuff #
CC = @gcc
CFGLAGS = -Wall -Werror -Wextra
# Remove #
REMOVE = @rm -f
# OBJS #
OBJS = ${SRC:.c=.o}
# check later if needed #
# INC_LIBFT = -I libs/Libft/includes
# INC_READLINE = -I libs/readline/include
# LIB #
LIBFT = libs/Libft/libft.a
# readline #
READLINE = libs/readline/libreadline.a
HISTORY = libs/readline/libhistory.a
# RUN #
RUN = @./minishell
# Source #
SRC = 	./src/main/main.c\
		./src/execution/fork.c\
		./src/cmds/echo.c\
		./src/cmds/pwd.c\
		./src/cmds/env.c\
		./src/cmds/cd.c\
		./src/cmds/export.c\
		./src/cmds/ft_exit.c\
		./src/cmds/unset.c\
		./src/main/init.c \
		./src/main/signal.c \
		./src/parsing/read_input.c \
		./src/parsing/check_input.c \
		./src/utils/linked_list_cmds.c \
		./src/execution/pipes.c
# Colors #
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
# ${CC} ${CFGLAGS} ${OBJS} -L libs/Libft -lft -L libs/readline -lreadline -lhistory ${INC_READLINE} -o ${NAME} #

all: lib $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		${CC} ${CFGLAGS} ${OBJS} -L libs/Libft -lft -lreadline -o ${NAME}
	@echo "$(GREEN)Done$(WHITE)"

lib:
	@make -s -C libs/Libft

#assert: CFLAGS += -DASSERT=1
#assert: fclean all
#	@python3 ./assert_minishell.py

clean:
	@make clean -s -C libs/Libft
	${REMOVE} ${OBJS}

fclean:clean
	@make fclean -s -C libs/Libft
	${REMOVE} ${NAME}
	@echo "$(RED)Cleaning done$(WHITE)"

re: fclean all

run: all
	${RUN}

.PHONY: all clean fclean re lib run