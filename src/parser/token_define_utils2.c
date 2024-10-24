/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:27:46 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 19:04:00 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	single_quote_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int		export;
	bool	inside_quotes;
	t_token	*new_token;
	char	*str;

	export = n;
	inside_quotes = true;
	single_quote_token_assist(lexer, &inside_quotes, &n);
	str = ft_substr(lexer->input, export, ((n - export) + 1));
	new_token = ft_token_new(str);
	free(str);
	new_token->type = TYPE_COMMAND;
	if (export > 0 && ((lexer->input[export - 1] < 10 \
		|| lexer->input[export - 1] > 12) && lexer->input[export - 1] != ' '))
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

int	double_quote_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int		export;
	bool	inside_quotes;
	t_token	*new_token;
	char	*str;

	export = n;
	inside_quotes = true;
	double_quote_token_assist(lexer, &inside_quotes, &n);
	str = ft_substr(lexer->input, export, ((n - export) + 1));
	new_token = ft_token_new(str);
	free(str);
	new_token->type = TYPE_COMMAND;
	if (export > 0 && ((lexer->input[export - 1] < 10 \
		|| lexer->input[export - 1] > 12) && lexer->input[export - 1] != ' '))
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}
