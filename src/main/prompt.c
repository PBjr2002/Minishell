/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/24 15:08:00 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	prompt(t_environment *info)
{
	t_lexer	*lexer;

	while (1)
	{
		lexer = ft_calloc(sizeof(t_lexer), 1);
		signal_decider(PARENT);
		global_info(NULL, info);
		lexer->invalid_lexer = false;
		store_input(lexer);
		add_history(lexer->input);
		if (!lexer->input)
		{
			free(lexer);
			exec_exit(0, 1);
		}
		else if (lexer->invalid_lexer == true || input_checker(lexer) == 0)
		{
			free(lexer);
			continue;
		}
		if (parser_and_exec(lexer, info) == 1)
			continue;	
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
		tree_cleaner(tree);
		printf("Syntax error\n");
		return (1);
	}
	global_info(tree, info);
	search_tree(tree, info, 0);
	tree_cleaner(tree);
	return (0);
}

/* input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m"); */

