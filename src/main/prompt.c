/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/19 18:11:11 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	prompt(t_environment *info)
{
	t_lexer	*lexer;
	t_token	*token_list;
	t_tree	*tree;

	lexer = ft_calloc(sizeof(t_lexer), 1);
	while (1)
	{
		signal_decider(PARENT);
		lexer->invalid_lexer = false;
		store_input(lexer);
		add_history(lexer->input);
		if (!lexer->input)
			exec_exit(0, NULL, tree, info);
		else if (lexer->invalid_lexer == true || input_checker(lexer) == 0)
			continue;
		token_list = tokenization(lexer);
		tree = parsing(token_list, info);
		info = tree_cleanup_function(tree, info);
		search_tree(tree, info);
	}
}

/* input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m"); */

