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

# Leak #
LEAK = valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --trace-children=yes ./minishell

EXECUTION = ./src/execution/execution.c \
			./src/execution/redirection/io_redirection.c \
			./src/execution/redirection/redirection_utils.c \
			./src/execution/child/path.c \
			./src/execution/child/child.c \
			./src/execution/child/execve.c \
			./src/execution/child/builtin.c \
			./src/execution/heredoc/heredoc.c \
			./src/execution/heredoc/heredoc_file_handler.c \
			./src/execution/child/cleanup.c

PARSING =	./src/parsing/list_christo.c \
			./src/parsing/list_redir_christo.c \
			./src/parsing/parsing_utils_1.c\
			./src/parsing/parsing_utils_2.c\
			./src/parsing/test_list.c\
			./src/parsing/list_utils.c

INPUT	= 	./src/input/read_input.c \
			./src/input/read_input_heredoc.c

PARSING =	./src/parsing/list_christo.c \
			./src/parsing/list_redir_christo.c \
			./src/parsing/parsing_utils_1.c\
			./src/parsing/parsing_utils_2.c\
			./src/parsing/test_list.c\
			./src/parsing/list_utils.c

UTILS = ./src/utils/strings/strjoin_path.c \
		./src/utils/strings/str_cutcut.c \
		./src/utils/env_functions.c \
		./src/utils/signal.c \
		./src/utils/mini_struct_functions.c \
		./src/utils/print_startup.c \
		./src/utils/strings/create_file_name.c \
		./src/utils/check_expandable.c \
		./src/utils/free_linked_list_exec.c

LEXER = ./src/lexer/lexer.c \
		./src/lexer/literal/literal.c \
		./src/lexer/literal/literal_string.c \
		./src/lexer/literal/literal_redir.c \
		./src/lexer/literal/literal_error.c

INTERPRETER = ./src/interpreter/interpreter.c \
			  ./src/interpreter/dollar/dollar_expandable.c \
			  ./src/interpreter/dollar/dollar_interpreter.c \
			  ./src/interpreter/quotes/quotes_interpreter.c \
			  ./src/interpreter/cut.c \
			  ./src/interpreter/dollar/dollar_length_handle.c

CMDS = ./src/cmds/echo.c \
		./src/cmds/pwd.c \
		./src/cmds/env.c \
		./src/cmds/cd.c \
		./src/cmds/export.c \
		./src/cmds/ft_exit.c \
		./src/cmds/unset.c

ERRORS = ./src/errors/error.c

SRC = 	./src/main.c \
		$(EXECUTION) \
		$(PARSING) \
		$(UTILS) \
		$(LEXER) \
		$(CMDS) \
		$(INTERPRETER) \
		$(INPUT) \
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

tester: CFLAGS += -D TESTER=1
tester: fclean all
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

leak: all
	${LEAK}

.PHONY: all clean fclean re lib run leak
