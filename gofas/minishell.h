/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:54 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/06/12 16:13:38 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "libft/libft.h"
# include "libft/get_next_line.h"

typedef struct s_token
{
	char					*str;
	int						index;
	struct s_token			*next;
}	t_token;

typedef struct s_redirect
{
	char 					*str;
	int						index;
	struct s_redirects		*next;
}	t_redirect;

typedef struct s_lexer
{
	char    				*str;
	int						index;
	struct s_lexer			*next;
}	t_lexer;

typedef struct s_pipe
{
	char    				*str;
	int						index;
	int						fd[2];
	struct s_pipe			*next;
}	t_pipe;

typedef struct s_simple_cmd
{
	char                    **str;
	t_redirect             *redirects;
	t_parser				*parser;
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
>d echo ola bom <a | <g wc -c >k

	>d <a echo ola bom
	<g >k wc -c
*/

//char, char*



//int, unsigned int, long, long long



//void



#endif