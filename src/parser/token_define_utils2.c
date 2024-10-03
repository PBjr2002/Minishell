/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:27:46 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/03 17:56:32 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	single_quote_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int		export;
	t_token	*new_token;

	export = n;
	n++;
	while (lexer->input[n])
	{
		n++;
		if (lexer->input[n] == '\'' && (lexer->input[n + 1] && lexer->input[n + 1] == ' '))
			break;
	}
	new_token = ft_token_new(ft_substr(lexer->input, export, ((n - export) + 1)));
	new_token->type = TYPE_COMMAND;
	if (export > 0 && (lexer->input[export - 1] < 10 
		|| lexer->input[export - 1] > 12) && lexer->input[export - 1] != ' ')
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

int double_quote_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int		export;
	t_token	*new_token;
	
	export = n;
	n++;
	while (lexer->input[n])
	{
		n++;
		if (lexer->input[n] == '"' && (lexer->input[n + 1] && lexer->input[n + 1] == ' '))
			break;
	}
	new_token = ft_token_new(ft_substr(lexer->input, export, ((n - export) + 1)));
	new_token->type = TYPE_COMMAND;
	if (export > 0 && ((lexer->input[export - 1] < 10 
		|| lexer->input[export - 1] > 12) || lexer->input[export - 1] != ' '))
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}
