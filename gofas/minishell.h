/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:54 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/19 16:30:31 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SINGLE_IN 1
# define SINGLE_OUT 2
# define DOUBLE_IN 3
# define DOUBLE_OUT 4
# define TYPE_DOLLAR 5
# define TYPE_PIPE 6
# define TYPE_ARGUMENT 7
# define TYPE_COMMAND 8
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft_gofas/libft.h"
# include "libft_gofas/get_next_line.h"
# include "libft_gofas/ft_printf.h"

typedef struct s_token
{
	char					*str;
	int						index;
	int						type;
	struct s_token			*next;
}	t_token;

/* typedef struct s_redirect
{
	char 					*str;
	int						index;
	struct s_redirects		*next;
}	t_redirect; */

typedef struct s_lexer
{
	char    				*input;
	char					**argv;
	int						argc;
	bool					invalid_lexer;
}	t_lexer;

typedef struct s_pipe
{
	int						index;
	int						fd[2];
	struct s_pipe			*next;
}	t_pipe;

typedef struct s_simple_cmd
{
	char                    **str;
	struct s_parser			*parser;
	struct s_simple_cmd		*next;
}	t_simple_cmd;

typedef struct s_parser
{
	char					**env;
	char					**export_env;
	pid_t					pid;
	t_pipe					*pipe;
	t_simple_cmd			*simple_commands;
}	t_parser;

/*
>d echo ola bom <a >o | <g wc -c $USER >k

	>d <a >o echo ola bom |
	lmiguel- <g >k wc -c 

*/

//char, char*



//int, unsigned int, long, long long

/* int 			redirect_token_define(t_lexer *lexer, int n); */

//void

void			store_input(t_lexer *lexer);
/* void 			tokenization(t_lexer *lexer); */

//lists

/* t_lexer			*ft_lexer_new(void);
t_token			*ft_token_new(char *str);
t_pipe			*ft_pipe_new(char *str, int index);
t_simple_cmd	*ft_simple_cmd_new(char *str); */

#endif