/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:56:14 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/27 16:05:16 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int 	export;
	t_token	*new_token;

	export = n;
	if (lexer->input[n] == '\'')
	{
		n++;
		while (lexer->input[n] != '\'')
			n++;
		new_token = ft_token_new(ft_substr(lexer->input, export, ((n - export) + 1)));
		ft_token_append(token_list, new_token, new_token->str);
	}
	else if (lexer->input[n] == '"')
	{
		n++;
		while (lexer->input[n] != '"')
				n++;
		new_token = ft_token_new(ft_substr(lexer->input, export, ((n - export) + 1)));
		ft_token_append(token_list, new_token, new_token->str);
	}
	n++;
	return (n);
}

int redirect_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	//recycle (export) to use as a pointer to where the redirect token is at. 
	//useful to send towards (redirect_token_solver)
	int 	export;
	t_token *new_token;

	export = n;
	n++;
	if (lexer->input[n + 1] == '<' || lexer->input[n + 1] == '>')
		n++;
	while ((lexer->input[n] > 9 && lexer->input[n] < 13) || lexer->input[n] == ' ')
		n++;
	while ((lexer->input[n] > 32 && lexer->input[n] < 127))
		n++;
	new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	new_token->type = redirect_token_type_solver(lexer, export);
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

int	dollar_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	//numbers, uppercase, lowercase or underscore only, everything else ends the dollar definer and exports the result under the DOLLAR type
	int export;
	t_token	*new_token;

	export = n;
	n++;
	while ((lexer->input[n] > 47 && lexer->input[n] < 58) 
		|| (lexer->input[n] > 64 && lexer->input[n] < 91) 
		|| (lexer->input[n] > 96 && lexer->input[n] < 123) 
		|| (lexer->input[n] == 95))
		n++;
	new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	new_token->type = TYPE_DOLLAR;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

int	pipe_token_define(t_token *token_list, int n)
{
	t_token *new_token;
	
	new_token = ft_token_new("|\0");
	ft_token_append(token_list, new_token, new_token->str);
	new_token->type = TYPE_PIPE;
	n++;
	return(n);
}

int com_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int 	export;
	t_token	*new_token;
	
	export = n;
	n++;
	while ((lexer->input[n] != '|') && (lexer->input[n] != ' ')
			&& (lexer->input[n] != '\'') && (lexer->input[n] != '"') 
			&& (lexer->input[n] != '$') && (lexer->input[n] != '<') 
			&& (lexer->input[n] != '>') && lexer->input[n])
		n++;
	new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	new_token->type = TYPE_COMMAND;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

/* int quote_token_remover(t_lexer *lexer, int n)
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
} */
