/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_solvers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:32:46 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/17 15:41:49 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//identifies which type the redirection token is
int redirect_token_type_solver(t_lexer *lexer, int n)
{
	int type;
	
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

