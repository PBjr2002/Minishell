CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SOURCES = main.c builtins.c builtins_helper.c builtins_helper2.c builtins_helper3.c echo.c\
			cd.c pwd.c export.c prompt.c env.c

OBJS_DIR = obj
OBJECTS = $(addprefix $(OBJS_DIR)/, $(SOURCES:%.c=%.o))

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

MERDA = $(LIBFT) -lreadline 

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(MERDA)

$(OBJS_DIR)/%.o:%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		rm -rf $(OBJS_DIR)

fclean: clean
		$(MAKE) fclean -C $(LIBFT_DIR)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re