/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:44:40 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/17 15:41:32 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//this function identifies commands and arguments
void command_id(t_token *token_list)
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
void command_expand (t_token *token_list, t_environment *env)
{
	int n;

	while (token_list)
	{
		n = 0;
		if (token_list->type == TYPE_COMMAND || token_list->type == TYPE_DOLLAR_COMMAND)
		{
			if (token_list->str[0] == '\'')
				token_list = token_list->next;
			else
			{
				while (token_list->str[n])
				{
					if (token_list->str[n] == '$')
					{
						token_list->str = ft_command_expander(token_list->str, env);
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

//everything inside the single quotes are treated as a word, no matter what they are.
//everything except dollar signs are treated as words inside double quotes
void	quote_token_remover(t_token *token, int export, int n)
{
	char *temp;
	
	while (token->str[n])
	{
	if (token->str[n] == '\'')
	{
		n++;
		export++;
		while (token->str[n] != '\'')
			n++;
		temp = token->str;
		token->str = ft_substr(token->str, export, (n - export));
		free(temp);
	}
	else if (token->str[n] == '"')
	{
		n++;
		export++;
		while (token->str[n] != '"')
		{
			if (token->str[n] == '$')
				token->type = TYPE_DOUBLE_QUOTE_EXPAND;
			n++;
		}
		temp = token->str;
		token->str = ft_substr(token->str, export, (n - export));
		free(temp);
	}
	n++;
	}
}

//cleans the redirection token, removing "< > << >>" as well as any spaces
void	redirection_handler(t_token *list, int n, int export)
{
	char	*temp;

	if (list->type == SINGLE_IN || list->type == SINGLE_OUT
		|| list->type == DOUBLE_IN || list->type == DOUBLE_OUT)
	{
		n++;
		if (list->type == DOUBLE_IN || list->type == DOUBLE_OUT)
			n++;
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