/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/26 15:08:38 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:

REMEMBER THIS ORDER:

    1. Reads command
    2. Tokenization 
    3. Command Identification x (done)
    4. Command Expansion x (URGENT DO NOW) (done, for some reason delegated to me)
    5. Quote Removal x (done)
    6. Redirections x (done)
    7. Command Execution 

	IMPORTANT

	Apparently, control and redirection operators cannot be limiters.
	As a reminder:


	Control operators are:

	newline, |, ||, &, &&, ;, ;;, ;&, ;;&, |&, (, )


	Redirection operators are:

	<, >, <<, >>, <&, >|, <←, <>, >&

*/

//this function takes care of the 3 sections of parsing highlighted with an x in the above list

#include "../../inc/parser.h"

t_tree	*parsing(t_token *token_list, t_environment *env)
{
	t_token	*temp;
	t_tree	*tree;
	int 	single;

	(void)env;
	temp = token_list;
	command_id(token_list);
	token_list = temp;
	command_expand(token_list, env);
	token_list = temp;
	while (token_list)
	{
		single = 0;
		single = single_quote_token_remover(token_list, 0, 0);
		if (single == 0)
			double_quote_token_remover(token_list, 0, 0);
		token_list = token_list->next;
	}
	token_list = temp;
	while (token_list)
	{
		redirection_handler(token_list, 0, 0);
		token_list = token_list->next;
	}
	token_list = temp;
	tree = tree_creation_function(token_list);
	return (tree);
}
