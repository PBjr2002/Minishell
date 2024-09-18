/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/18 15:06:21 by pauberna         ###   ########.fr       */
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
	while (token_list)
	{
		//ft_printf("Token index: %d, Token type: %d, Token contains: %s\n", 
		//token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	}
	token_list = temp;
	command_expand(token_list, env);
	//ft_printf("-------------INITIATING COMMAND EXPANDER-------------\n");
	while (token_list)
	{
		//ft_printf("Token index: %d, Token type: %d, Token contains: %s\n", 
		//token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	}
	token_list = temp;
	//ft_printf("-------------INITIATING QUOTE REMOVER----------------\n");
	while (token_list)
	{
		quote_token_remover(token_list, 0, 0);
		//ft_printf("Token index: %d, Token type: %d, Token contains: %s\n", 
		//token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	}
	token_list = temp;
	//ft_printf("-------------INITIATING REDIRECT HANDLER-------------\n");
	while (token_list)
	{
		redirection_handler(token_list, 0, 0);
		//ft_printf("Token index: %d, Token type: %d, Token contains: %s\n", 
		//token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	}
	token_list = temp;
	//add function that searches and destroys (marks?) empty tokens (or exclude them from tree)
	tree = tree_creation_function(token_list);
	//printf("whoop\n");
	/* ft_printf("-------------INITIATING TREE CREATION----------------\n");
	while (tree)
	{
		ft_printf("Branch parent: Token type: %d, Token contains: %s\n", 
		token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	} */
	return (tree);
}



