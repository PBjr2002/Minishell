/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/17 16:43:34 by pauberna         ###   ########.fr       */
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
		if (ft_strlen(lexer->input) == 0 || !lexer->input)
		{
			free(lexer->input);
			exec_exit(0, NULL, tree, info);
		}
		else if (lexer->invalid_lexer == true || input_checker(lexer) == 0)
			continue;
		token_list = tokenization(lexer);
		tree = parsing(token_list, info);
		search_tree(tree, info);
		//if (new_av && new_av[0])
		//{
		//	while (new_av[new_ac])
		//		new_ac++;
		//	decider(new_ac, new_av, info);
		//	free_env(new_av);
		//}
	}
}

/* input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m"); */

