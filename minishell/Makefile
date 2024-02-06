NAME 		= minishell

CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

SRC 		= main.c starter/init.c starter/lexer.c starter/check_quote.c starter/token_handle.c \
			helper/lexer_utils.c helper/lexer_clear_utils.c helper/lst_utils.c helper/env_utils.c \
			helper/lst_utils2.c helper/str_utils.c helper/utils.c starter/signals.c\
			parser/parser.c parser/parser_utils.c parser/redirection.c parser/command_utils.c \
			exec/execution.c  exec/execution2.c exec/redirections.c exec/heredoc.c \
			error_free/common_error.c error_free/free_memory.c error_free/exit.c  \
			built_in/main_built_in.c built_in/exec_unset.c  built_in/exec_echo.c\
			built_in/exec_cd.c built_in/exec_export.c built_in/exec_exit.c\
			expander/expander.c expander/expander_utils.c expander/delete_quotes.c\
			expander/expander_utils2.c helper/exec_utils.c helper/hd_utils.c
OBJ         =  $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o $@

$(NAME): 	$(OBJ)
			make all -C ./libft
			$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME) -I/Users/fabdul-k/.brew/Cellar/readline/8.2.7/include -L/Users/fabdul-k/.brew/Cellar/readline/8.2.7/lib -lreadline

all 	:	$(NAME)

clean	: 
			rm -f $(OBJ)

fclean	: 	clean
			make fclean -C ./libft
			rm -f $(NAME)

re 		: 	fclean all

.PHONY	:	all clean fclean re