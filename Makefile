CC = cc
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
NAME = minishell

SRC = $(addprefix src/, $(SOURCES))
SOURCES =	main/main.c main/prompt.c \
			builtins/builtins.c builtins/builtins_helper.c builtins/builtins_helper2.c \
			builtins/builtins_helper3.c builtins/builtins_helper4.c builtins/builtins_helper5.c\
			builtins/builtins_helper6.c builtins/builtins_helper7.c builtins/builtins_helper8.c builtins/builtins_helper9.c\
			builtins/builtins_helper10.c builtins/echo.c builtins/cd.c builtins/pwd.c builtins/export.c\
			builtins/env.c builtins/set_builtins_fds.c builtins/exec_other.c builtins/redirects.c builtins/echo_helper.c\
			builtins/fds.c builtins/fds2.c builtins/fds3.c\
			expansions/expansions.c expansions/expander_utils.c expansions/expander_utils2.c expansions/signal.c \
			parser/lexer_test.c parser/token_define_utils.c parser/token_define_utils2.c parser/token_define_utils3.c \
			parser/token_define_utils4.c parser/token_solvers.c \
			parser/tree_and_list_append.c parser/tree_and_list_append2.c parser/tree_and_list_init.c \
			parser/tree_cleanup_utils.c parser/tree_creation_utils.c \
			parser/tree_creation_utils2.c parser/tree_creation_utils3.c parser/tree_creation_utils4.c \
			parser/tree_creation_utils5.c \
			parser/tokenization.c parser/parsing_utils.c parser/parsing_utils2.c parser/parsing_utils3.c \
			parser/parsing_helper.c parser/parsing_helper2.c parser/parsing_helper3.c parser/parsing_helper4.c \
			parser/parsing.c

OBJS_DIR = obj
OBJECTS = $(addprefix $(OBJS_DIR)/, $(SRC:src/%.c=%.o))

LIBFT_DIR = ./inc/libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFLAG = $(LIBFT) -lreadline

Color_Off='\033[0m'       # Text Reset
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
ICyan='\033[0;96m'        # Cyan


MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}


all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBFLAG)
		$(MSG1)

$(OBJS_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		rm -rf $(OBJS_DIR)
		$(MSG2)

fclean: clean
		$(MAKE) fclean -C $(LIBFT_DIR)
		rm -f $(NAME)
		$(MSG3)

re: fclean all

.PHONY: all clean fclean re