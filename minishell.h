/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:31:27 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/11 14:25:52 by pauberna         ###   ########.fr       */
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
}				t_line;

/* ls -l | grep a > file

t_line0:
cmd = ls -l;
input = STDIN_FILENO
output = pipe[1];
n = 0;
parser :
	-redirect = NULL;
	-n = 0;
	-token :
		-str = "|";
		-n = 0;
		-next = NULL;
		-prev = NULL;
	-next = NULL;
	-prev = NULL;
next = t_line1;
prev = NULL;

t_line1:
cmd = grep a;
input = pipe[0];
output = file;
n = 1;
parser :
	-redirect = file;
	-n = 0;
	-token :
		-str = ">";
		-n = 0;
		-next = NULL;
		-prev = NULL;
	-next = NULL;
	-prev = NULL;
next = NULL;
prev = t_line0; */


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
void	prompt(int ac, char **av, char **envp);

//builtins.c
void	decider(int ac, char **av, char **envp);

//builtins_helper.c
int		search_env_line(char **envp, char *line_to_search);
int		search_part_line(char **envp, char *line_to_search, size_t len);
char	*return_env_line(char **envp, int index);
void	remove_env_line(char **envp, int index);
char	**add_env_line(char **envp, char *info_to_add);

//echo.c
void	exec_echo(int fd, char **av);

//cd.c
void	exec_cd(int fd, char **av, char **envp);

//pwd.c
void	exec_pwd(int fd, char **envp);

//export.c
char	**env_to_print(char **envp);
void	exec_export(int fd, char **av, char **envp);
void	sort_env(char **new_env, int limit);
void	print_export(int fd, char **sorted);

#endif