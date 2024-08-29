/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/29 15:50:14 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:

REMEMBER THIS ORDER:

    1. Reads command
    2. Tokenization 
    3. Command Identification x (done)
    4. Command Expansion
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

#include "minishell.h"

//this function takes care of the 3 sections of parsing highlighted with an x in the above list

t_token	*parsing(t_token *token_list)
{
	t_token	*temp;

	command_id(token_list);
	temp = token_list;
	while (token_list)
	{
		ft_printf("Token index: %d, Token type: %d, Token contains: %s\n", 
		token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	}
	token_list = temp;
	ft_printf("-------------INITIATING QUOTE REMOVER----------------\n");
	while (token_list)
	{
		quote_token_remover(token_list, 0, 0);
		ft_printf("Token index: %d, Token type: %d, Token contains: %s\n", 
		token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	}
	token_list = temp;
	ft_printf("-------------INITIATING REDIRECT HANDLER-------------\n");
	while (token_list)
	{
		redirection_handler(token_list, 0, 0);
		ft_printf("Token index: %d, Token type: %d, Token contains: %s\n", 
		token_list->index, token_list->type, token_list->str);
		token_list = token_list->next;
	}
	token_list = temp;
	//add dunction that searches and destroys (marks?) empty tokens (or exclude them from tree)
	return (token_list);
}
