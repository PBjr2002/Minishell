/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:56:14 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 19:59:24 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//simply copies the quotes and everything inside them 
int	quote_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	if (lexer->input[n] == '\'')
		n = single_quote_token_define(lexer, token_list, n);
	else if (lexer->input[n] == '"')
		n = double_quote_token_define(lexer, token_list, n);
	n++;
	return (n);
}

//recycle (export) to use as a pointer to where the redirect token is at. 
//useful to send towards (redirect_token_solver)
int	redirect_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int			export;
	t_token		*new_token;
	bool		single_quote;
	bool		double_quote;

	export = n;
	new_token = NULL;
	if ((lexer->input[n] == '<' && lexer->input[n + 1] == '<') \
		|| (lexer->input[n] == '>' && lexer->input[n + 1] == '>'))
		n++;
	n++;
	while ((lexer->input[n] > 9 && lexer->input[n] < 13) \
		|| lexer->input[n] == ' ')
		n++;
	redirect_token_define_assist(lexer, &single_quote, &double_quote, &n);
	new_token = redirect_token_define_assist2(lexer, new_token, export, n);
	new_token->type = redirect_token_type_solver(lexer, export);
	if (export > 0 && ((lexer->input[export - 1] < 10 \
		|| lexer->input[export - 1] > 12) || lexer->input[export - 1] != ' '))
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

//numbers, uppercase, lowercase or underscore only, 
//everything else ends the dollar definer and 
//exports the result under the DOLLAR type
int	dollar_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int			export;
	t_token		*new_token;
	char		*str;

	export = n++;
	dollar_token_define_assist(lexer, &n);
	str = ft_substr(lexer->input, export, (n - export));
	new_token = ft_token_new(str);
	if (lexer->input[n] == '"' || lexer->input[n] == '\'')
		new_token->invalid_expand = true;
	free(str);
	new_token->type = TYPE_DOLLAR;
	if (export > 0 && ((lexer->input[export - 1] < 10 \
		|| lexer->input[export - 1] > 12) \
		&& lexer->input[export - 1] != ' '))
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

//this function simply adds a pipe token, no need to get fancy
int	pipe_token_define(t_token *token_list, int n)
{
	t_token	*new_token;

	new_token = ft_token_new("|\0");
	ft_token_append(token_list, new_token, new_token->str);
	new_token->type = TYPE_PIPE;
	n++;
	return (n);
}

//transcribes everything that isn't checked by the 
//tokenization function as a command
int	com_token_define(t_lexer *lexer, t_token *token_list, int n)
{
	int			export;
	bool		single_quote;
	bool		double_quote;
	t_token		*new_token;
	char		*str;

	export = n;
	n++;
	com_token_define_assist(lexer, &single_quote, &double_quote, &n);
	str = ft_substr(lexer->input, export, (n - export));
	new_token = ft_token_new(str);
	free(str);
	new_token->type = TYPE_COMMAND;
	if (export > 0 && ((lexer->input[export - 1] < 10 \
		|| lexer->input[export - 1] > 12) \
		&& lexer->input[export - 1] != ' '))
		new_token->append_before = true;
	ft_token_append(token_list, new_token, new_token->str);
	return (n);
}

//ls | grep s >>out | wc <out | cat