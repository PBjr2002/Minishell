/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:32:46 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/17 15:42:11 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/parser.h"


int bracket_dollar_solver(t_lexer *lexer, char *str, int n)
{
	//numbers, uppercase, lowercase or underscore only, everything else ends the dollar bracket solver and exports the result under the DOLLAR type
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

int bracket_solver(t_lexer *lexer, int n)
{
	//everything inside the single quotes are treated as a word, no matter what they are.
	//everything except dollar signs are treated as words inside double quotes
	int export;

	export = n;
	if (lexer->input[n] == '\'')
	{
		n++;
		export++;
		while (lexer->input[n] != '\'')
			n++;
		lexer->test_input = ft_substr(lexer->input, export, (n - export));
		ft_printf("This is the solved single quotes: %s\n", lexer->test_input);
		return (n);
	}
	else if (lexer->input[n] == '"')
	{
		n++;
		export++;
		while (lexer->input[n] != '"')
		{
			if (lexer->input[n] == '$')
				n = bracket_dollar_solver(lexer, lexer->input, n);
			else
				n++;
		}
		lexer->test_input = ft_substr(lexer->input, export, (n - export));
		ft_printf("This is the solved double quotes: %s\n", lexer->test_input);
		return (n);
	}
	return (n);
}
