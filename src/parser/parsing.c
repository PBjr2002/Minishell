/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/07 14:28:17 by lmiguel-         ###   ########.fr       */
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

	(void)env;
	temp = token_list;
	command_id(token_list);
	token_list = temp;
	command_expand(token_list, env);
	token_list = temp;
	while (token_list)
	{
		if (quote_decider(token_list) == 0)
			single_quote_token_remover(token_list, 0, 0);
		else if (quote_decider(token_list) == 1 && token_list->expand == true)
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

int		quote_decider(t_token *token_list)
{
	int n;

	n = 0;
	while (token_list && token_list->str && token_list->str[n])
	{
		if (token_list->str[n] == '\'')
			return (0);
		else if (token_list->str[n] == '"')
			return (1);
		n++;
	}
	return (2);
}