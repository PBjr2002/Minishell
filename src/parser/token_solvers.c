/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_solvers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:32:46 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 16:11:27 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//identifies which type the redirection token is
int	redirect_token_type_solver(t_lexer *lexer, int n)
{
	int	type;

	type = 0;
	if (lexer->input[n] == '<' && lexer->input[n + 1] == '<')
		type = DOUBLE_IN;
	else if (lexer->input[n] == '<' && lexer->input[n + 1] != '<')
		type = SINGLE_IN;
	else if (lexer->input[n] == '>' && lexer->input[n + 1] == '>')
		type = DOUBLE_OUT;
	else if (lexer->input[n] == '>' && lexer->input[n + 1] != '>')
		type = SINGLE_OUT;
	return (type);
}
