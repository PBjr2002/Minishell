CC = cc
CFLAGS = -g -Wall -Wextra -Werror
NAME = minishell

SOURCES = main.c builtins.c builtins_helper.c builtins_helper2.c builtins_helper3.c echo.c\
			cd.c pwd.c export.c prompt.c env.c signal.c expansions.c

OBJS_DIR = obj
OBJECTS = $(addprefix $(OBJS_DIR)/, $(SOURCES:%.c=%.o))

LIBFT_DIR = ./libft/
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

$(OBJS_DIR)/%.o:%.c
	mkdir -p $(OBJS_DIR)
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