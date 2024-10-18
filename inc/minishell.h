/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:31:27 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/18 13:44:10 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_cd
{
	char	*cwd;
	char	*tmp;
	char	*new_cwd;
	char	*env_pwd;
	char	*old_pwd;
	char	**new_envp;
	char	**new_export;
}				t_cd;

typedef struct s_global
{
	t_tree			*tree;
	t_environment	*envr;
}				t_global;

//main.c

//prompt.c
void		prompt(t_environment *info);
int			parser_and_exec(t_lexer *lexer, t_environment *info);

//builtins.c
void		decider(t_tree *tree, t_tree *cmd, t_environment *envr);
int			redirect_solver(t_tree *tree, t_environment *envr);
void		pipe_setup(t_tree *tree);

//builtins_helper.c
char		**copy_env(char **envp, int mode);
int			copy_env_helper(char **new_env, char **envp, char *lvl, int mode);
char		**remove_env_line(char **envp, int index);
int			remove_env_helper(char **envp, char **tmp_env, int index);
char		**add_env_line(char **envp, char *info_to_add);

//builtins_helper2.c
int			ft_strlen2(char *str, int sep);
int			return_value(char **envp, int index);
int			search_env_line(char **envp, char *line_to_search);
int			search_part_line(char **envp, char *line_to_search, size_t len);

//builtins_helper3.c
char		*return_env_line(char **envp, int index);
char		*return_part_line(char **envp, int index, int mode);
void		free_env(char **env);
char		*ft_getpid(void);
char		*cut_strhelper(t_expand *ex, t_environment *envr,
				char *str, char *var);

//builtins_helper4.c
char		**build_av(t_tree *tree, t_tree *cmd);
int			build_av_helper(t_tree *cmd, t_tree *tree, t_tree *tmp, char **av);
int			build_av_helper2(t_tree *tree, char **av, char *stmp, int len);
void		tree_cleaner(t_tree *tree, int mode);
void		token_cleaner(t_token *token_list);

//builtins_helper5.c
void		search_pipe(t_tree *tree, t_environment *envr);
int			search_redirect(t_tree *tree, t_environment *envr, int mode);
char		**replace_line(char **envp, char *info_to_add);
char		**replace_value(char **envp, int index, int value);
int			replace_value_helper(char **envp, char **tmp_env,
				char *nb, int index);

//builtins_helper6.c
char		**env_to_print(char **envp);
void		sort_env(char **new_env, int limit);
void		print_export(int fd, char **sorted);
void		print_export_helper(char **sorted, int fd, int n, int i);
void		print_export_helper2(char **sorted, int fd, int n, int i);

//builtins_helper7.c
int			check_line(char *line);
int			exec_here_doc(t_tree *tree, t_environment *envr);
void		here_doc_helper(t_tree *tree, t_environment *envr, int *fd);
void		here_doc_clean(t_tree *tree, t_environment *envr,
				char *input, int *fd);
void		prepare_exit(t_tree *tree, t_environment *envr);

//builtins_helper8.c
int			check_expansion(char *str);
void		expand_everything(t_tree *tree, t_environment *envr);
void		exec_cmd(t_tree *tree, t_environment *envr);
void		exec_child(t_tree *tree, t_environment *envr, int mode);
void		real_exec_cmd(t_tree *tree, t_environment *envr);

//builtins_helper9.c
void		ch_signal(int signal);
t_global	global_info(t_tree *tree, t_environment *envr);
void		exit_checker(t_tree *tree);
void		get_rest_helper(char *str, t_expand *ex);
int			path_creator_checker(char *path);

//builtins_helper10.c
void		cd_helper(t_environment *envr, t_cd *cd);
void		cd_helper2(t_tree *cmd, t_environment *envr, t_cd *cd);
int			cd_helper3(t_tree *tree, t_tree *cmd, t_cd *cd);
int			cd_helper4(t_tree *tree, t_tree *cmd, t_cd *cd);
void		cd_cleaner(t_environment *envr, t_cd *cd, int mode);

//set_builtins_fds.c
void		set_builtins_fds(t_tree *tree);
void		set_builtins_fds_helper(t_tree *tree);
void		set_builtins_fds_helper2(t_tree *tree);
void		set_builtins_fds_helper3(t_tree *tree);
void		set_builtins_fds_helper4(t_tree *tree);

//redirects.c
int			redirect_single_in(t_tree *tree);
int			redirect_single_out(t_tree *tree);
int			redirect_double_in(t_tree *tree, t_environment *envr);
int			redirect_double_out(t_tree *tree);

//fds.c
void		clean_all_fds(int fds);
void		close_fds(t_tree *tree, t_environment *envr);
void		close_specific_fds(t_environment *envr, int fd_in, int fd_out);
void		set_fds(t_tree *tree, char **av, char *path, int *fd);

//fds2.c
void		close_fds_helper(t_tree *tree, t_environment *envr);
void		close_fds_helper2(t_tree *tree, t_environment *envr);
void		close_fds_helper3(t_tree *tree, t_environment *envr);
void		close_fds_helper4(t_tree *tree, t_environment *envr);

//fds3.c
void		set_fds_helper(t_tree *tree, int *fd);
void		set_fds_helper2(t_tree *tree, int *fd);
void		set_fds_helper3(t_tree *tree, int *fd);
void		set_fds_helper4(t_tree *tree, int *fd);

//echo.c
int			exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr);
void		echo_helper(t_tree *tree, t_tree *cmd,
				t_environment *envr, int *nl);
int			echo_helper2(t_tree *tree, int *nl);
int			echo_helper3(t_tree *tree, int *nl, int *space);
void		echo_helper4(t_tree *tree, t_tree *cmd, t_environment *envr);

//cd.c
int			exec_cd(t_tree *tree, t_tree *cmd, t_environment *envr);

//pwd.c
int			exec_pwd(t_tree *cmd);

//export.c
int			exec_export(t_tree *tree, t_tree *cmd, t_environment *envr);
void		export_helper(t_tree *tree, t_tree *cmd, t_environment *envr);
void		export_helper2(t_tree *tree, t_environment *envr);
void		export_helper3(t_tree *cmd, t_tree *tree, t_environment *envr);
int			check_argument(char *str);

//env.c
int			exec_env(t_tree *cmd, t_environment *env);
int			exec_unset(t_tree *tree, t_environment *envr);
void		exec_exit(int signal, int mode, int write);
void		closed_pipe(int signal, siginfo_t *info, void *context);

//exec_other.c
char		*check_path(char **paths, char *cmd);
void		free_paths(char **paths);
char		*path_creator(t_tree *cmd, t_environment *envr);
void		exec_other(t_tree *tree, t_tree *cmd, t_environment *envr);
void		executer(t_tree *cmd, t_tree *tree,
				t_environment *envr, char *path);

//signal.c
void		signal_decider(t_signal type);
void		signal_decider_part2(t_signal type, struct sigaction sa);
void		ignore(struct sigaction *sa, int signal);
void		ctrl_c(int signal, siginfo_t *info, void *context);

//expansions.c
int			check_for_dollar(char *str, int n);
char		*connect(char *pre, char *pos);
char		*exec_expansion(char *str, t_environment *envr);
void		get_rest(char *str, t_expand *ex);
void		cut_str(char *str, t_expand *ex, t_environment *envr);

#endif