# Executable #
NAME = minishell

# Compile stuff #
CC = @gcc
#CC = gcc
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

EXECUTION = ./src/execution/execution.c \
			./src/execution/redirection/io_redirection.c \
			./src/execution/redirection/redirection_utils.c \
			./src/execution/child/path.c \
			./src/execution/child/child.c \
			./src/execution/child/execve.c \
			./src/execution/heredoc/heredoc.c

PARSING = ./src/parsing/read_input.c \
		./src/parsing/check_input.c \
		./src/parsing/list_christo.c \
		./src/parsing/list_redir_christo.c

UTILS = ./src/utils/linked_list_cmds.c \
		./src/utils/strjoin_path.c \
		./src/utils/place_holder.c \
		./src/utils/str_cutcut.c

LEXER = ./src/lexer/lexer.c \
		./src/lexer/literal/literal.c \
		./src/lexer/literal/literal_string.c \
		./src/lexer/literal/literal_redir.c \
		./src/lexer/literal/literal_error.c \
		./src/lexer/interpreter/dollar_interpreter.c \
		./src/lexer/interpreter/quotes_interpreter.c \
		./src/lexer/interpreter/dollar_expandable.c

CMDS = ./src/cmds/echo.c \
		./src/cmds/pwd.c \
		./src/cmds/env.c \
		./src/cmds/cd.c \
		./src/cmds/export.c \
		./src/cmds/ft_exit.c \
		./src/cmds/unset.c

ERRORS = ./src/errors/error.c

MAIN = ./src/main/main.c \
		./src/main/init.c \
		./src/main/signal.c

SRC = $(MAIN) \
		$(EXECUTION) \
		$(PARSING) \
		$(UTILS) \
		$(LEXER) \
		$(CMDS) \
		$(ERRORS)


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
#	make -C libs/Libft

assert: CFLAGS += -DASSERT=1
assert: fclean all
	@python3 ./assert_minishell.py

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