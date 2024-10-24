/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:29:58 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 16:25:17 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:

REMEMBER THIS ORDER:

    1. Reads command
    2. Tokenization x (done)
    3. Command Identification
    4. Command Expansion
    5. Quote Removal
    6. Redirections
    7. Command Execution

------------------------------TOKENS--------------------------------

Tokens are separated by  | & ; ( ) < > space tab newline 

A token that doesn't contain any meta-characters and isn't in quotes
is considered a word.

A token that contains no quotes and has at least one meta-character 
is considered an operator.

Control operators are:

newline | || & && ; ;; ;& ;;& |& ( )

Redirection operators are:

< > << >> <& >& >/ <← <>

Examples, with output after:

< infile ls | wc < d

<infile >output ls
<d wc

7 tokens:

echo, $USER, output.txt = 3 words

3 spaces, 1 > = 4 meta-characters, 
of which > is a redirection operator

' ' = disables all meta characters

" " = disables all meta characters except $

------------------------------COMMANDS------------------------------

2 types of commands: simple and compound

Simple commands are composed of a command with arguments, 
or multiple simple commands.

Redirections are checked and applied one by one before commands

Example:

if test1 doesn't exist and we were to run this command:

>test2 echo $USER <test1

test2 would be created, but bash would return a 
"test1: no such file or directory" error and quit.

*/

#include "../../inc/parser.h"

/* this recieves the user input and separates it 
	into tokens to send to the token list, 
	in order of appearance */
t_token	*tokenization(t_lexer *lexer)
{
	int			n;
	t_token		*temp;

	n = 0;
	temp = ft_token_new("temp\0");
	while (lexer->input && lexer->input[n])
	{
		while ((lexer->input[n] > 9 && lexer->input[n] < 13) \
			|| lexer->input[n] == ' ')
			n++;
		if (lexer->input[n] == '\'' || lexer->input[n] == '"')
			n = quote_token_define(lexer, temp, n);
		else if (lexer->input[n] == '<' || lexer->input[n] == '>')
			n = redirect_token_define(lexer, temp, n);
		else if (lexer->input[n] == '$' && (n > 0 && \
			((lexer->input[n - 1] > 9 && lexer->input[n - 1] < 13) \
			|| lexer->input[n - 1] == ' ')))
			n = dollar_token_define(lexer, temp, n);
		else if (lexer->input[n] == '|')
			n = pipe_token_define(temp, n);
		else if (lexer->input[n])
			n = com_token_define(lexer, temp, n);
	}
	temp = temp_list_cleaner(temp);
	return (temp);
}

//clears the temp token that serves as a starting reference to create the 
//token list
t_token	*temp_list_cleaner(t_token *list)
{
	t_token	*temp;

	temp = list;
	if (list->next)
	{
		list = list->next;
		list->previous = NULL;
	}
	free(temp->str);
	free(temp);
	return (list);
}
