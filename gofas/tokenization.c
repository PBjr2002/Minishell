/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:29:58 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/27 15:41:16 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:

REMEMBER THIS ORDER:

    1. Reads command
    2. Tokenization x (in progress)
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

#include "minishell.h"

/* this recieves the user input and separates it into tokens to send to the tree. */

t_token *tokenization(t_lexer *lexer)
{
	int	n;
	int type;
	t_token	*temp;
	
	n = 0;
	temp = ft_token_new("temp\0");
	while (lexer->input && lexer->input[n])
	{
		type = 0;
		while ((lexer->input[n] > 9 && lexer->input[n] < 13) || lexer->input[n] == ' ')
			n++;
		if (lexer->input[n] == '\'' || lexer->input[n] == '"')
			n = quote_token_define(lexer, temp, n);
		else if (lexer->input[n] == '<' || lexer->input[n] == '>')
			n = redirect_token_define(lexer, temp, n);
		else if (lexer->input[n] == '$')
			n = dollar_token_define(lexer, temp, n);
		else if (lexer->input[n] == '|')
			n = pipe_token_define(temp, n);
		else
			n = com_token_define(lexer, temp, n);
	}
	return (temp->next);
}



