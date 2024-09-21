/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/21 13:47:18 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	prompt(t_environment *info)
{
	t_lexer	*lexer;
	t_token	*token_list;
	t_tree	*tree;

	while (1)
	{
		lexer = ft_calloc(sizeof(t_lexer), 1);
		signal_decider(PARENT);
		lexer->invalid_lexer = false;
		store_input(lexer);
		add_history(lexer->input);
		if (!lexer->input)
		{
			free(lexer);
			exec_exit(0, NULL, NULL, info);
		}
		else if (lexer->invalid_lexer == true || input_checker(lexer) == 0)
		{
			free(lexer);
			continue;
		}
		token_list = tokenization(lexer);
		free(lexer->input);
		free(lexer);
		tree = parsing(token_list, info);
		//token_cleaner(token_list);
		info = tree_cleanup_function(tree, info);
		if (info->status == 2)
		{
			tree_cleaner(tree);
			printf("Syntax error\n");
			continue;
		}
		search_tree(tree, info, 0);
		tree_cleaner(tree);
	}
}

/* input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m"); */

