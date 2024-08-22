# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 14:28:19 by lmiguel-          #+#    #+#              #
#    Updated: 2024/08/22 13:52:50 by lmiguel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
FLAGS		= -Wall -Werror -Wextra

SRC			= 	$(SOURCES)
SOURCES		=	lexer_test.c\
				utils1.c\
				tree_and_list_append.c\
				tree_and_list_init.c\

OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

LIBFT_DIR = ./libft_gofas/
LIBFT = $(LIBFT_DIR)libft.a

READLINE = $(LIBFT) -lreadline
			
all: 		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(FLAGS) $(OBJ) -o $@ $(READLINE)

$(OBJ_DIR)/%.o: %.c
			mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)			

clean:
			$(MAKE) clean -C $(LIBFT_DIR)
			rm -rf $(OBJ_DIR)

fclean:		clean
			$(MAKE) fclean -C $(LIBFT_DIR)
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re