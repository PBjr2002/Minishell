/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:31:27 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/18 16:12:22 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"

typedef struct s_token
{
	char					*str;
	int						index;
	struct s_token			*next;
}				t_token;

typedef struct s_redirect
{
	char					*str;
	int						index;
	struct s_redirects		*next;
}				t_redirect;

typedef struct s_lexer
{
	char					*str;
	int						index;
	struct s_lexer			*next;
}				t_lexer;

typedef struct s_pipe
{
	char					*str;
	int						index;
	int						fd[2];
	struct s_pipe			*next;
}				t_pipe;

typedef struct s_simple_cmd
{
	char					**str;
	t_redirect				*redirects;
	struct s_parser			*parser;
	struct s_simple_cmd		*next;
}				t_simple_cmd;

typedef struct s_parser
{
	char					**env;
	char					**export_env;
	pid_t					pid;
	t_pipe					*pipe;
	t_simple_cmd			*simple_commands;
}				t_parser;

/* typedef struct s_token
{
	char			*str;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_parser
{
	char			*redirect;
	int				index;
	t_token			*token;
	struct s_parser	*next;
	struct s_parser	*prev;
}				t_parser;

typedef struct s_line
{
	char			**cmd;
	int				input;
	int				output;
	int				index;
	t_parser		*redirect;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line; */


// 1- Reads command
// 2- Tokenization
// 3- Command Identification
// 4- Command Expansion
// 5- Quote Removal
// 6- Redirections
// 7- Command Execution

/* 
	Builtins:
	-echo with -n option
	-cd
	-pwd
	-export
	-unset
	-env
	-exit

	Metacharacters :
	- |
	- > and <
	- *
	- ~
	- $
	- ^

	Having a history

	Use of absolute path(search in pipex)
	Use of relative path

	
 */

//main.c

//prompt.c
void	prompt(int ac, char **av, t_parser *info);

//builtins.c
void	decider(int ac, char **av, t_parser *info);

//builtins_helper.c
char	**copy_env(char **envp, int mode);
char	**remove_env_line(char **envp, int index);
char	**add_env_line(char **envp, char *info_to_add);
char	**replace_line(char **envp, char *info_to_add);
char	**replace_value(char **envp, int index, int value);

//builtins_helper2.c
int		ft_strlen2(char *str, int sep);
int		return_value(char **envp, int index);
int		search_env_line(char **envp, char *line_to_search);
int		search_part_line(char **envp, char *line_to_search, size_t len);

//builtins_helper3.c
char	*return_env_line(char **envp, int index);
char	*return_part_line(char **envp, int index, int mode);

//echo.c
void	exec_echo(int fd, char **av);

//cd.c
void	exec_cd(int fd, char **av, t_parser *info);

//pwd.c
void	exec_pwd(int fd);

//export.c
char	**env_to_print(char **envp);
void	exec_export(int fd, char **av, t_parser *info);
void	sort_env(char **new_env, int limit);
void	print_export(int fd, char **sorted);

//env.c
char	*check_path(char **paths, char **av);
void	exec_env(int fd, t_parser *info);
void	exec_unset(char **av, t_parser *info);
void	exec_exit(int signal, char **av);
void	exec_other(int fd, char **av, t_parser *info);

#endif