/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:54 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/23 14:24:08 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SINGLE_IN 1
# define SINGLE_OUT 2
# define DOUBLE_IN 3
# define DOUBLE_OUT 4
# define TYPE_DOLLAR 5
# define TYPE_PIPE 6
# define TYPE_ARGUMENT 7
# define TYPE_COMMAND 8
# define TYPE_DOUBLE_QUOTE_EXPAND 9
# define TYPE_DOLLAR_COMMAND 10
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
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
# include "libft/ft_printf.h"

typedef enum s_signal
{
	PARENT,
	CHILD,
	HERE_DOC,
	IGNORE,
	PIPE_CLOSED,
}			t_signal;

typedef struct s_token
{
	char					*str;
	int						index;
	int						type;
	bool					expand;
	bool					append_before;
	bool					null_char;
	bool					invalid_expand;
	struct s_token			*previous;
	struct s_token			*next;
}	t_token;

typedef struct s_environment
{
	char					**env;
	char					**export_env;
	int						status;
	int						old_status;
	int						fds;
	int						path_flag;
	pid_t					pid;
}	t_environment;

typedef struct s_tree
{
	char					*str;
	int						pipeline; //if this is 0, no pipes exist
	int						type;
	int						fd_in;
	int						fd_out;
	int						*heredoc_input_fd; //default value is 0
	bool					expand;
	bool					solved;
	bool					append_before;
	bool					null_char;
	bool					invalid_expand;
	struct s_tree			*parent;
	struct s_tree			*left;
	struct s_tree			*right;
}	t_tree;

typedef struct s_lexer
{
	char					*input;
	char					*test_input;
	bool					invalid_lexer;
}	t_lexer;

//char, char*
char			*command_expander_assist2(char *str, int *n,
					t_environment *env);
char			*ft_command_expander(char *str, t_environment *env, int n);
char			*dollar_removal(char *str, int expand_start,
					int expand_end, t_environment *env);
char			*env_search(char *expand, t_environment *env);

//int, unsigned int, long, long long
int				check_valid_pipes(t_tree *treetop, t_tree *temp);
int				check_valid_redirects(t_tree *treetop);
int				check_valid_redirects_2(t_tree *treetop);
int				com_token_define(t_lexer *lexer, t_token *token_list, int n);
int				command_expander_assist1(char *str, int *n,
					bool *s_q, bool *d_d);
int				dollar_token_define(t_lexer *lexer, t_token *token_list, int n);
int				double_quote_token_define(t_lexer *lexer,
					t_token *token_list, int n);
int				input_checker(t_lexer *lexer);
int				limiter_double_quote_remover(t_token *token_list,
					int quote_start, int n);
int				limiter_single_quote_remover(t_token *token_list,
					int quote_start, int n);
int				pipe_scanner(t_token *token_list);
int				pipe_token_define(t_token *token_list, int n);
int				quote_token_define(t_lexer *lexer,
					t_token *token_list, int n);
int				quote_decider(t_token *token_list);
int				quote_dollar_solver(t_lexer *lexer, char *str, int n);
int				redirect_token_define(t_lexer *lexer,
					t_token *token_list, int n);
void			redirect_token_define_assist(t_lexer *lexer, bool *s_q,
					bool *d_q, int *n);
int				redirect_token_type_solver(t_lexer *lexer, int n);
int				single_quote_token_define(t_lexer *lexer,
					t_token *token_list, int n);
int				syntax_checker_assist1(t_tree *treetop, int type);

//void
void			com_token_define_assist(t_lexer *lexer, bool *s_q,
					bool *d_q, int *n);
void			command_expand(t_token *token_list, t_environment *env);
void			command_id(t_token *token_list);
void			double_quote_dissection(t_token *token,
					int quote_start, int quote_end);
void			double_quote_token_assist(t_lexer *lexer, bool *inside_quotes,
					int *n);
void			double_quote_token_remover(t_token *token,
					int export, int n);
void			empty_double_quote_removal(t_token *token,
					int quote_start, int quote_end);
void			empty_single_quote_removal(t_token *token,
					int quote_start, int quote_end);
void			find_pipes_assist(bool *first_pipe_detected, int *pipeline);
void			ft_argument_branch_attach(t_tree *tree, t_tree *new);
void			ft_branch_attach(t_tree *tree, t_tree *new,
					int branch_type, int pipeline);
void			ft_command_branch_attach1(t_tree *tree, t_tree *new);
void			ft_command_branch_attach2(t_tree *tree, t_tree *new);
void			ft_fill_tree1(t_token *token_list, t_tree *current,
					int pipeline);
void			ft_fill_tree2(t_token *token_list, t_tree *current,
					int pipeline, int pipenum);
void			ft_fill_tree2_assist2(t_token *token_list,
					t_tree *current, int pipeline);
void			ft_fill_tree2_finisher(t_token *token_list,
					t_tree *current, int pipeline);
void			ft_fill_tree_zero_assist2(t_token *token_list,
					t_tree *current, int pipeline);
void			ft_redirect_branch_attach2(t_tree *tree, t_tree *new);
void			ft_token_append(t_token *token_list, t_token *new, char *str);
void			ft_scan_for_redirects1(t_token *token_list,
					t_tree *current, int pipeline);
void			ft_scan_for_redirects2(t_token *token_list,
					t_tree *current, int pipeline);
void			ft_scan_for_redirects3(t_token *t_list,
					t_tree *current, int pipeline);
void			limiter_dollar_remover(t_token *token_list);
void			limiter_empty_double_quote_removal(t_token *token,
					int quote_start, int quote_end);
void			limiter_empty_single_quote_removal(t_token *token,
					int quote_start, int quote_end);
void			limiter_double_quote_dissection(t_token *token,
					int quote_start, int quote_end);
void			limiter_handler(t_token *token_list);
void			limiter_single_quote_dissection(t_token *token,
					int quote_start, int quote_end);
void			midlist_token_append(t_token *token_list, t_token *new);
void			limiter_dollar_assist(t_token *token_list, int n);
void			limiter_double_quote_assist(t_token *token,
					int quote_start, int quote_end);
void			limiter_double_quote_assist2(t_token *token,
					int quote_start, int quote_end);
void			limiter_single_quote_asssist(t_token *token,
					int quote_start, int quote_end);
void			limiter_single_quote_asssist2(t_token *token,
					int quote_start, int quote_end);
void			parsing_double_quote_assist(t_token *token,
					int quote_start, int quote_end);
void			parsing_double_quote_assist2(t_token *token,
					int quote_start, int quote_end);
void			parsing_single_quote_assist(t_token *token,
					int quote_start, int quote_end);
void			parsing_single_quote_assist2(t_token *token,
					int quote_start, int quote_end);
void			parsing_quote_assist(t_token *token_list);
void			post_command_expand_check(t_token *token_list);
void			prev_and_remaining_free(char *previous, char *remaining);
void			quote_scanner(char *str, int n,
					bool *double_quote, bool *single_quote);
void			quote_token_remover(t_token *token, int export, int n);
void			redirection_handler(t_token *list, int n, int export);
void			single_quote_dissection(t_token *token,
					int quote_start, int quote_end);
void			single_quote_token_assist(t_lexer *lexer,
					bool *inside_quotes, int *n);
void			single_quote_token_remover(t_token *token, int export, int n);
void			store_input(t_lexer *lexer);
void			store_input_quote_assist(t_lexer *lexer, bool *o_s_q,
					bool *o_d_q, int *n);
void			dollar_token_define_assist(t_lexer *lexer, int *n);
void			command_expand_assist(t_token *token_list, t_environment *env,
					int *n);

//lists and trees
t_tree			*ft_redirect_branch_attach1_assist2(t_tree *tree,
					t_tree *new);
t_tree			*ft_redirect_branch_attach1_assist3(t_tree *tree,
					t_tree *new);
t_tree			*ft_redirect_branch_attach1_assist4(t_tree *tree,
					t_tree *new);
t_tree			*find_pipes(t_token *t_list, t_tree *top, int pipenum);
t_tree			*ft_branch_new(t_token *token, char *str,
					int type, int pipeline);
t_tree			*ft_tree_spawn(t_token *t_list);
t_tree			*ft_construct_pipelines_zero(t_token *token_list,
					t_tree *top, int pipeline);
t_tree			*ft_construct_pipelines(t_token *token_list,
					t_tree *top, int pipenum, int pipeline);
t_tree			*ft_pipe_branch_attach(t_tree *tree, t_tree *new);
t_tree			*ft_fill_tree_zero(t_token *token_list,
					t_tree *current, int pipeline);
t_tree			*ft_fill_tree_zero_assist(t_token *token_list,
					t_tree *current, int pipeline);
t_tree			*ft_fill_tree2_assist(t_token *token_list,
					t_tree *current, int pipeline);
t_tree			*ft_command_branch_attach_zero(t_tree *tree,
					t_tree *new, t_token *token_list);
t_tree			*ft_redirect_branch_attach1(t_tree *tree, t_tree *new);
t_tree			*ft_redirect_branch_attach1_assist(t_tree *tree, t_tree *new);
t_tree			*tree_creation_function(t_token *token_list);
t_token			*ft_token_new(char *str);
t_token			*redirect_token_define_assist2(t_lexer *lexer,
					t_token *new_token, int export, int n);
t_tree			*parsing(t_token *token_list, t_environment *env);
t_token			*temp_list_cleaner(t_token *list);
t_token			*tokenization(t_lexer *lexer);
t_environment	*env_setup(char **envp);
t_environment	*tree_cleanup_function(t_tree *treetop, t_environment *info);

#endif