/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:15 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/21 14:43:20 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:

REMEMBER THIS ORDER:

    1. Reads command
    2. Tokenization 
    3. Command Identification x (done)
    4. Command Expansion x (done)
    5. Quote Removal x (done)
    6. Redirections x (done)
    7. Command Execution 

	IMPORTANT

	Apparently, control and redirection operators cannot be limiters.
	As a reminder:


	Control operators are:

	newline, |, ||, &, &&, ;, ;;, ;&, ;;&, |&, (, )


	Redirection operators are:

	<, >, <<, >>, <&, >|, <←, <>, >&

*/

//this function takes care of the 3 sections of 
//parsing highlighted with an x in the above list

#include "../../inc/parser.h"

t_tree	*parsing(t_token *token_list, t_environment *env)
{
	t_token	*temp;
	t_tree	*tree;

	(void)env;
	temp = token_list;
	command_id(token_list);
	token_list = temp;
	command_expand(token_list, env);
	token_list = temp;
	while (token_list)
	{
		parsing_quote_assist(token_list);
		token_list = token_list->next;
	}
	token_list = temp;
	while (token_list)
	{
		redirection_handler(token_list, 0, 0);
		token_list = token_list->next;
	}
	token_list = temp;
	tree = tree_creation_function(token_list);
	while (tree->parent)
		tree = tree->parent;
	return (tree);
}

void	limiter_handler(t_token *token_list)
{
	int	n;

	n = 0;
	limiter_dollar_remover(token_list);
	while (token_list->str && token_list->str[n])
	{
		if (token_list->str[n] == '"')
			n = limiter_double_quote_remover(token_list, n, n);
		else if (token_list->str[n] == '\'')
			n = limiter_single_quote_remover(token_list, n, n);
		else
			n++;
	}
}

void	limiter_double_quote_dissection(t_token *token,
		int quote_start, int quote_end)
{
	char	*previous_and_quotes;
	char	*temp;
	char	*previous;
	char	*remaining;
	char	*in_quotes;

	temp = token->str;
	if (quote_start == 0)
		limiter_double_quote_assist(token, quote_start, quote_end);
	else if (quote_end == (int)ft_strlen(token->str))
		limiter_double_quote_assist2(token, \
			quote_start, quote_end);
	else
	{
		in_quotes = ft_substr(token->str, quote_start + 1,
				((quote_end - 1) - quote_start));
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1,
				((ft_strlen(token->str)) - quote_end));
		previous_and_quotes = ft_strjoin(previous, in_quotes);
		token->str = ft_strjoin(previous_and_quotes, remaining);
		return (free(previous), free(remaining), free(in_quotes),
			free(temp), free(previous_and_quotes));
	}
}

void	limiter_dollar_remover(t_token *token_list)
{
	int		n;
	bool	inside_quote;

	n = 0;
	inside_quote = false;
	while (token_list->str && token_list->str[n])
	{
		if (token_list->str[n] == '\'' || token_list->str[n] == '"')
		{
			if (inside_quote == false)
				inside_quote = true;
			else
				inside_quote = false;
		}
		if (token_list->str[n] == '$' \
			&& (token_list->str[n + 1] && (token_list->str[n + 1] == '"' \
			|| token_list->str[n + 1] == '\'')) \
			&& (inside_quote == false))
			limiter_dollar_assist(token_list, n);
		n++;
	}
}

int	quote_decider(t_token *token_list)
{
	int	n;

	n = 0;
	while (token_list && token_list->str && token_list->str[n])
	{
		if (token_list->type == DOUBLE_IN)
			return (2);
		else if (token_list->str[n] == '\'')
			return (0);
		else if (token_list->str[n] == '"')
			return (1);
		n++;
	}
	return (3);
}
