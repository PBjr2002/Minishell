/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:56:14 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/17 15:41:46 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//simply copies the quotes and everything inside them (could give them a type...)
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
		new_token->type = TYPE_COMMAND;
		ft_token_append(token_list, new_token, new_token->str);
	}
	else if (lexer->input[n] == '"')
	{
		n++;
		while (lexer->input[n] != '"')
				n++;
		new_token = ft_token_new(ft_substr(lexer->input, export, ((n - export) + 1)));
		new_token->type = TYPE_COMMAND;
		ft_token_append(token_list, new_token, new_token->str);
	}
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
	while ((lexer->input[n] > 32 && lexer->input[n] < 127))
		n++;
	new_token = ft_token_new(ft_substr(lexer->input, export, (n - export)));
	new_token->type = redirect_token_type_solver(lexer, export);
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

//numbers, uppercase, lowercase or underscore only, everything else ends the dollar definer and exports the result under the DOLLAR type
int	dollar_token_define(t_lexer *lexer, t_token *token_list, int n)
{
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

//this function simply adds a pipe token, no need to get fancy
int	pipe_token_define(t_token *token_list, int n)
{
	t_token *new_token;
	
	new_token = ft_token_new("|\0");
	ft_token_append(token_list, new_token, new_token->str);
	new_token->type = TYPE_PIPE;
	n++;
	return(n);
}

//transcribes everything that isn't checked by the tokenization function as a command
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
