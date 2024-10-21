/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/21 14:06:36 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	prompt(t_environment *info, t_lexer *lexer)
{
	while (1)
	{
		lexer = ft_calloc(sizeof(t_lexer), 1);
		signal_decider(PARENT);
		global_info(NULL, info, -2, -2);
		lexer->invalid_lexer = false;
		store_input(lexer);
		add_history(lexer->input);
		if (maybe_free(lexer, info) == 1)
			continue ;
		if (parser_and_exec(lexer, info) == 1)
			continue ;
	}
}

int	parser_and_exec(t_lexer *lexer, t_environment *info)
{
	t_token		*token_list;
	t_tree		*tree;

	token_list = tokenization(lexer);
	free(lexer->input);
	free(lexer);
	tree = parsing(token_list, info);
	token_cleaner(token_list);
	info = tree_cleanup_function(tree, info);
	if (info->status == 2)
	{
		tree_cleaner(tree, 0);
		printf("Syntax error\n");
		info->status = 0;
		return (1);
	}
	global_info(tree, info, -1, -1);
	expand_everything(tree, info);
	exec_cmd(tree, info, 0);
	clean_all_fds(info->fds);
	tree_cleaner(tree, 0);
	return (0);
}

int	maybe_free(t_lexer *lexer, t_environment *info)
{
	if (!lexer->input)
	{
		free(lexer);
		exec_exit(info->status, 1, 0);
	}
	else if (lexer->input[0] == '\0')
		return (free(lexer), 1);
	else if (lexer->invalid_lexer == true || input_checker(lexer) == 0)
	{
		free(lexer);
		info->status = 2;
		return (printf("Syntax error\n"), 1);
	}
	return (0);
}

/* input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m"); */
