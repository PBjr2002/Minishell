/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:31:27 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/24 13:27:56 by pauberna         ###   ########.fr       */
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

typedef struct s_global
{
	t_tree 			*tree;
	t_environment	*envr;
}				t_global;

//main.c

//prompt.c
void	prompt(t_environment *info);
int		parser_and_exec(t_lexer *lexer, t_environment *info);

//builtins.c
void	decider(t_tree *tree, t_tree *cmd, t_environment *envr);
void	search_tree(t_tree *tree, t_environment *envr, int mode);
int		redirect_solver(t_tree *tree, t_environment *envr);
void	pipe_setup(t_tree *tree);
void	fd_setup(t_tree *tree, int mode);

//builtins_helper.c
char	**copy_env(char **envp, int mode);
int		copy_env_helper(char **new_env, char **envp, char *lvl, int mode);
char	**remove_env_line(char **envp, int index);
int		remove_env_helper(char **envp, char **tmp_env, int index);
char	**add_env_line(char **envp, char *info_to_add);

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
int		build_av_helper(t_tree *cmd, t_tree *tree, t_tree *tmp, char **av);
void	tree_cleaner(t_tree *tree);
void	token_cleaner(t_token *token_list);
void	fd_closer(t_tree *tree, int mode);

//builtins_helper5.c
void	search_pipe(t_tree *tree, t_environment *envr);
int		search_redirect(t_tree *tree, t_environment *envr);
char	**replace_line(char **envp, char *info_to_add);
char	**replace_value(char **envp, int index, int value);
int		replace_value_helper(char **envp, char **tmp_env, char *nb, int index);

//builtins_helper6.c
char	**env_to_print(char **envp);
void	sort_env(char **new_env, int limit);
void	print_export(int fd, char **sorted);
void	print_export_helper(char **sorted, int fd, int n, int i);
void	print_export_helper2(char **sorted, int fd, int n, int i);

//builtins_helper7.c
int			check_line(char *line);
int			exec_here_doc(t_tree *tree, t_environment *envr);
void		here_doc_cleaner(t_tree *tree, t_environment *envr, char *input, int *fd);
t_global	global_info(t_tree *tree, t_environment *envr);

//echo.c
int		exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr);
void	echo_helper(t_tree *tree, t_tree *cmd, t_environment *envr);

//cd.c
int		exec_cd(t_tree *tree, t_tree *cmd, t_environment *envr);

//pwd.c
int		exec_pwd(t_tree *cmd);

//export.c
int		exec_export(t_tree *tree, t_tree *cmd, t_environment *envr);
void	export_helper(t_tree *tree, t_tree *cmd, t_environment *envr);
void	export_helper2(t_tree *tree, t_environment *envr);
void	export_helper3(t_tree *cmd, t_tree *tree, t_environment *envr);
int		check_argument(char *str);

//env.c
int		exec_env(t_tree *cmd, t_environment *env);
int		exec_unset(t_tree *tree, t_environment *envr);

//exec_other.c
char	*check_path(char **paths, char *cmd);
void	free_paths(char **paths);
char	*path_creator(t_tree *cmd, t_environment *envr);
void	exec_other(t_tree *tree, t_tree *cmd, t_environment *envr);
void	executer(t_tree *cmd, t_tree *tree, t_environment *envr, char *path);

//signal.c
void	signal_decider(t_signal type);
void	prepare_exit(t_tree *tree, t_tree *cmd, t_environment *envr);
void	ignore(struct sigaction *sa, int signal);
void	exec_exit(int signal);
void	ctrl_c(int signal, siginfo_t *info, void *context);

//expansions.c
int		check_for_dollar(char *str, int n);
char	*connect(char *pre, char *pos);
char	*exec_expansion(char *str, t_environment *envr);
void	get_rest(char *str, t_expand *ex);
void	cut_str(char *str, t_expand *ex, t_environment *envr);

#endif