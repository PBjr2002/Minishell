/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:56:39 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/24 10:56:05 by pauberna         ###   ########.fr       */
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
				if (lexer->input[(*n) + 1])
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
