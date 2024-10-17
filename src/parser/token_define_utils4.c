/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:56:39 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 19:06:01 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	double_quote_token_assist(t_lexer *lexer, bool *inside_quotes, int *n)
{
	int	z;

	if (lexer->input[*n] == '"')
		*n = *n + 1;
	while (lexer->input[*n])
	{
		if (lexer->input[*n] == '"')
		{
			if (*inside_quotes == true)
			{
				*inside_quotes = false;
				break ;
			}
		}
		z = *n + 1;
		if ((lexer->input[z] && \
			(lexer->input[z] == ' ' || lexer->input[z] == '|' \
			|| lexer->input[z] == '<' || lexer->input[z] == '>'))
			&& *inside_quotes == false)
			break ;
		*n = *n + 1;
	}
}
