/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:44:40 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/16 14:44:18 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//this function identifies commands and arguments
void	command_id(t_token *token_list)
{
	bool	first_word;
	
	first_word = true;
	while (token_list->index != 0)
		token_list = token_list->previous;
	while (token_list)
	{
		if ((token_list->type == TYPE_COMMAND || token_list->type == TYPE_DOLLAR) && first_word == true)
			{
				first_word = false;
				token_list->expand = false;
				if (token_list->type == TYPE_DOLLAR)
					token_list->type = TYPE_DOLLAR_COMMAND;
			}
		else if (token_list->type == TYPE_PIPE)
			first_word = true;
		else if (token_list->type == TYPE_COMMAND && first_word == false)
			token_list->type = TYPE_ARGUMENT;
		token_list = token_list->next;
	}
}

//this function will scan all commands and expand them if necessary
void	command_expand(t_token *token_list, t_environment *env)
{
	int 	n;
	
	while (token_list && token_list->str)
	{
		n = 0;
		if (token_list->type == TYPE_COMMAND || token_list->type == TYPE_DOLLAR_COMMAND)
		{
			if (token_list->str && token_list->str[0] == '\'')
				token_list = token_list->next;
			else
			{
				while (token_list->str && token_list->str[n])
				{
					if (token_list->str[n] == '$')
					{
						token_list->str = ft_command_expander(token_list->str, env);
						post_command_expand_check(token_list);
						break ;
					}
					n++;
				}
				token_list = token_list->next;
			}
		}
		else
			token_list = token_list->next;
	}
}

//cleans the redirection token, removing "< > << >>" as well as any spaces
void	redirection_handler(t_token *list, int n, int export)
{
	char	*temp;

	if (list->str)
	{	
		if (list->type == SINGLE_IN || list->type == SINGLE_OUT
			|| list->type == DOUBLE_IN || list->type == DOUBLE_OUT)
		{
			n++;
			if (list->type == DOUBLE_IN || list->type == DOUBLE_OUT)
				n++;
			if (list->type == DOUBLE_IN)
				list->expand = false;
			while ((list->str[n] > 9 && list->str[n] < 13) || list->str[n] == ' ')
				n++;
			export = n;
			while (list->str[n])
				n++;
			temp = list->str;
			list->str = ft_substr(list->str, export, (n - export));
			free(temp);
		}
	}
}

//everything inside the single quotes are treated as a word, no matter what they are.
void	single_quote_token_remover(t_token *token, int quote_start, int n)
{
	int quote_end;

	quote_end = 0;
	while (token->str && token->str[n])
	{
		if (token->str[n] == '\'')
		{
			quote_start = n;
			n++;
			while (token->str[n] && token->str[n] != '\'')
				n++;
			quote_end = n;
			n = 0;
			token->expand = false;
			if (quote_end == quote_start + 1)
			{
				empty_single_quote_removal(token, quote_start, quote_end);
				continue;
			}
			else
				single_quote_dissection(token, quote_start, quote_end);
		}
	n++;
	}
}

// everything except dollar signs are treated as words inside double quotes
// export and n starts as 0, ALWAYS
// example cases... "e""c""h""o" ""echo ech""o echo""
void	double_quote_token_remover(t_token *token, int quote_start, int n)
{
	int quote_end;

	quote_end = 0;
	while (token->str && token->str[n])
	{
		if (token->str[n] == '"')
		{
			quote_start = n;
			n++;
			while (token->str[n] && token->str[n] != '"')
				n++;
			quote_end = n;
			n = 0;
			if (quote_end == quote_start + 1)
			{
				empty_double_quote_removal(token, quote_start, quote_end);
				continue;
			}
			else
				double_quote_dissection(token, quote_start, quote_end);
		}
	n++;
	}
}
