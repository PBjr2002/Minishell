/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_solvers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:32:46 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/27 14:06:23 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote_dollar_solver(t_lexer *lexer, char *str, int n)
{
	//numbers, uppercase, lowercase or underscore only, everything else ends the dollar quote solver and exports the result under the DOLLAR type
	int export;
	
	export = n;
	n++;
	while ((str[n] > 47 && str[n] < 58) || (str[n] > 64 && str[n] < 91) 
		|| (str[n] > 96 && str[n] < 123) || (str[n] == 95))
		n++;
	lexer->test_input = ft_substr(str, export, (n - export));
	ft_printf("This is the solved dollar in quotes: %s\n", lexer->test_input);
	//INSERT DESTINATION FOR OUTPUT ft_substr(*str, export, (n - export))
	return (n);
}

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

