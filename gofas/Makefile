# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 14:28:19 by lmiguel-          #+#    #+#              #
#    Updated: 2024/08/28 15:49:08 by lmiguel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc -g
FLAGS		= -Wall -Werror -Wextra

SRC			= 	$(SOURCES)
SOURCES		=	lexer_test.c\
				token_define_utils.c\
				token_solvers.c\
				tree_and_list_append.c\
				tree_and_list_init.c\
				tokenization.c\
				parsing_utils.c\

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