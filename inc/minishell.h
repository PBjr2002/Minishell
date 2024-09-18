/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:31:27 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/18 11:56:08 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_1_H
# define MINISHELL_1_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include "parser.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"

typedef struct s_expand
{
	char	*pos;
	char	*value;
	int		n;
	int		i;
	int		a;
}				t_expand;

//main.c

//prompt.c
void	prompt(t_environment *info);

//builtins.c
void	decider(t_tree *tree, t_environment *info);
void	search_tree(t_tree *tree, t_environment *envr);
void	redirect_solver(t_tree *tree, t_tree *cmd);

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
void	free_env(char **env);
char	*ft_getpid(void);
char	*cut_strhelper(t_expand *ex, t_environment *envr, char *str, char *var);

//builtins_helper4.c
char	**build_av(t_tree *tree, t_tree *cmd);

//echo.c
void	exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr);

//cd.c
void	exec_cd(t_tree *tree, t_tree *cmd, t_environment *envr);

//pwd.c
void	exec_pwd(t_tree *cmd);

//export.c
char	**env_to_print(char **envp);
void	exec_export(t_tree *tree, t_tree *cmd, t_environment *envr);
void	sort_env(char **new_env, int limit);
void	print_export(int fd, char **sorted);
int		check_line(char *line);
int		check_argument(char *str);

//env.c
char	*check_path(char **paths, char *cmd);
void	exec_env(t_tree *cmd, t_environment *env);
char	*path_creator(t_tree *cmd, t_environment *envr);
void	exec_unset(t_tree *tree, t_environment *envr);
void	exec_other(t_tree *tree, t_tree *cmd, t_environment *envr);

//signal.c
void	signal_decider(t_signal type);
void	prepare_exit(t_tree *tree, t_tree *cmd, t_environment *envr);
void	ignore(struct sigaction *sa, int signal);
void	exec_exit(int signal, t_tree *tree, t_tree *cmd, t_environment *envr);
void	ctrl_c(int signal, siginfo_t *info, void *context);

//expansions.c
int		check_for_dollar(char *str, int n);
char	*connect(char *pre, char *pos);
char	*exec_expansion(char *str, t_environment *envr);
void	get_rest(char *str, t_expand *ex);
void	cut_str(char *str, t_expand *ex, t_environment *envr);

#endif