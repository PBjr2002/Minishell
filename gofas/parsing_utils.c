/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:44:40 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/28 15:35:06 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function identifies commands and arguments

void command_id(t_token *token_list)
{
	t_token *temp;
	bool	first_word;
	
	first_word = true;
	temp = token_list;
	if (token_list)
	while (token_list->index != 0)
		token_list = token_list->previous;
	while (token_list)
	{
		if (token_list->type == TYPE_COMMAND && first_word == true)
			first_word = false;
		else if (token_list->type == TYPE_PIPE)
			first_word = true;
		else if (token_list -> type == TYPE_COMMAND && first_word == false)
			token_list->type = TYPE_ARGUMENT;
		token_list = token_list->next;
	}
}
