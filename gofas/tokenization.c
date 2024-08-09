/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:29:58 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/06/17 16:30:48 by lmiguel-         ###   ########.fr       */
/*   Updated: 2024/06/17 18:39:01 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:
REMEMBER THIS ORDER:
    1. Reads command
    2. Tokenization x
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

void tokenization(t_lexer *lexer)
{
	int	n;
	int type;

	n = 0;
	while (lexer->input[n])
	{
		type = 0;
		if ((lexer->input[n] > 9 && lexer->input[n] < 13) || lexer->input[n] == ' ')
			n++;
		else if (lexer->input[n] == '<' || lexer->input[n] == '>')
		{
			type = redirect_token_define(lexer, n);
			if (type == TYPE_DOUBLE_INPUT_REDIRECT || type == TYPE_DOUBLE_OUTPUT_REDIRECT)
				n++;
			create_new_token(lexer->input[n], type, n);
		}
		else if (lexer->input[n] == '$')
			create_new_token(lexer->input[n], TYPE_DOLLAR, n);
		else if (lexer->input[n] == '|')
			create_new_token(lexer->input[n], TYPE_PIPE, n);
		else
			create_new_token(lexer->input[n], TYPE_STRING, n);
		n++;
	}
}

int redirect_token_define(t_lexer *lexer, int n)
{
	int type;

	type = 0;
	if (lexer->input[n] == '<' && lexer->input[n + 1] == '<')
	{
		type = TYPE_DOUBLE_INPUT_REDIRECT;
		n++;	
	}
	else if (lexer->input[n] == '<' && lexer->input[n + 1] != '<')
		type = TYPE_SINGLE_INPUT_REDIRECT;
	else if (lexer->input[n] == '>' && lexer->input[n + 1] == '>')
	{
		type = TYPE_DOUBLE_OUTPUT_REDIRECT;
		n++;	
	}
	else if (lexer->input[n] == '>' && lexer->input[n + 1] != '>')
		type = TYPE_SINGLE_OUTPUT_REDIRECT;
	return (type);
}

