/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:56:14 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/07 14:21:41 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//simply copies the quotes and everything inside them (could give them a type...)
int quote_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	if (lexer->input[n] == '\'')
		single_quote_token_define(lexer, token_list, n);
	else if (lexer->input[n] == '"')
		double_quote_token_define(lexer, token_list, n);
	n++;
	return (n);
}

//recycle (export) to use as a pointer to where the redirect token is at. 
//useful to send towards (redirect_token_solver)
int redirect_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int 	export;
	t_token *new_token;

	export = n;
	if ((lexer->input[n] == '<' && lexer->input[n + 1] == '<') 
		|| (lexer->input[n] == '>' && lexer->input[n + 1] == '>'))
		n++;
	n++;
	while ((lexer->input[n] > 9 && lexer->input[n] < 13) || lexer->input[n] == ' ')
		n++;
	while ((lexer->input[n] > 32 && lexer->input[n] < 127
		&& lexer->input[n] != 60 && lexer->input[n] != 62))
		n++;
	if ((n - export) < 2)
		new_token = ft_token_new(NULL);
	else
		new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	new_token->type = redirect_token_type_solver(lexer, export);
	if ((lexer->input[export - 1] < 10 || lexer->input[export - 1] > 12) || lexer->input[export - 1] != ' ')
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

//numbers, uppercase, lowercase or underscore only, everything else ends the dollar definer and exports the result under the DOLLAR type
int	dollar_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int 		export;
	t_token		*new_token;

	export = n++;
	while ((lexer->input[n] > 47 && lexer->input[n] < 58) 
		|| (lexer->input[n] > 64 && lexer->input[n] < 91) 
		|| (lexer->input[n] > 96 && lexer->input[n] < 123) 
		|| (lexer->input[n] == 95) || (lexer->input[n] == 36) || (lexer->input[n] == 63))
		n++;
	if	((lexer->input[n] != '|') && (lexer->input[n] != ' ')
		&& (lexer->input[n] != '\'') && (lexer->input[n] != '"') 
		&& (lexer->input[n] != '<') && (lexer->input[n] != '>') 
		&& lexer->input[n])
	{
		while ((lexer->input[n] != '|') && (lexer->input[n] != ' ')
			&& (lexer->input[n] != '\'') && (lexer->input[n] != '"') 
			&& (lexer->input[n] != '<') && (lexer->input[n] != '>') && lexer->input[n])
			n++;
		new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	}
	else
		new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	new_token->type = TYPE_DOLLAR;
	if ((lexer->input[export - 1] < 10 || lexer->input[export - 1] > 12) || lexer->input[export - 1] != ' ')
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

//this function simply adds a pipe token, no need to get fancy
int	pipe_token_define(t_token *token_list, int n)
{
	t_token *new_token;
	
	new_token = ft_token_new(ft_strdup("|\0"));
	ft_token_append(token_list, new_token, new_token->str);
	new_token->type = TYPE_PIPE;
	n++;
	return(n);
}

//transcribes everything that isn't checked by the tokenization function as a command
int com_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int 		export;
	t_token		*new_token;
	
	export = n;
	n++;
	while ((lexer->input[n] != '|') && (lexer->input[n] != ' ')
			&& (lexer->input[n] != '\'') && (lexer->input[n] != '"') 
			&& (lexer->input[n] != '<') && (lexer->input[n] != '>') 
			&& lexer->input[n])
		n++;
	new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	new_token->type = TYPE_COMMAND;
	if (export > 0 && (lexer->input[export - 1] < 10 || lexer->input[export - 1] > 12) && lexer->input[export - 1] != ' ')
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

