# Executable #
NAME = minishell

# Compile stuff #
CC = @gcc
CFGLAGS = -Wall -Werror -Wextra

# Remove #
REMOVE = @rm -f

# OBJS #
OBJS = ${SRC:.c=.o}

# includes #
LIBFT = libs/Libft/libft.a
READLINE = libs/readline/libreadline.a
READHISTORY = libs/readline/libhistory.a

# Path for libs #
Path_LIBFT = libs/Libft/
PATH_READLINE = libs/readline/
PATH_READHISTORY = libs/readline/

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
		./src/execution/redirection.c \
		./src/utils/strjoin_path.c \
		./src/execution/path.c \
		./src/execution/heredoc.c \
		./src/utils/place_holder.c \
		./src/utils/mini_split.c \
		./src/lexer/lexer.c \
		./src/lexer/redirection_check.c \
		./src/lexer/literal.c

# Colors #
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

# Check if linux or mac, add a flag depending on the os #
# ifeq ($(OS), Linux)
# 	FLAGS = $(LINUX)
# else ifeq ($(OS), Darwin)
# 	FLAGS = $(MAC)
#         ,----,
#    ___.`      `,
#    `===  D     :
#      `'.      .'
#         )    (                   ,
#        /      \_________________/|
#       /                          |
#      |                           ;
#      |               _____       /
#      |      \       ______7    ,'
#      |       \    ______7     /
#       \       `-,____7      ,'   
# ^~^~^~^`\                  /~^~^~^~^
#   ~^~^~^ `----------------' ~^~^~^
#  ~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~

all: lib $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		${CC} ${CFGLAGS} ${OBJS} -lreadline -lncurses ${READLINE} ${READHISTORY} ${LIBFT} -o ${NAME}
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