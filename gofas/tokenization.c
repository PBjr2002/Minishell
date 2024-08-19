/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:29:58 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/19 18:20:03 by lmiguel-         ###   ########.fr       */
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

/* this identifies and assigns a type to each token present in the lexer input. Pretty sure. */

#include "minishell.h"

void tokenization(t_lexer *lexer, t_token *token)
{
	int	n;
	int j;
	int type;
	t_token *tokens;
	
	n = 0;
	j = 0;
	while (lexer->input[n])
	{
		type = 0;
		while ((lexer->input[n] > 9 && lexer->input[n] < 13) || lexer->input[n] == ' ')
			n++;
		j = n;
		if (lexer->input[n] == '\'' || lexer->input[n] == '"')
			bracket_solver(lexer->input[n], n);
		if (lexer->input[n] == '<' || lexer->input[n] == '>')
		{
			type = redirect_token_define(lexer, n);
			if (type == DOUBLE_IN || type == DOUBLE_OUT)
				n++;
			create_new_token(lexer->input[j], type, n);
		}
		else if (lexer->input[n] == '$')
			create_new_token(lexer->input[j], TYPE_DOLLAR, n);
		else if (lexer->input[n] == '|')
			create_new_token(lexer->input[j], TYPE_PIPE, n);
		else
			com_arg_definer(lexer->input[j], n);
		n++;
	}
}

int bracket_solver(t_lexer *lexer, int n)
{
	int export;

	export = n;
	if (lexer->input[n] == '\'')
	{
		n++;
		export++;
		while (lexer->input[n] != '\'')
			n++;
		//INSERT DESTINATION FOR OUTPUT ft_substr(lexer->input, export, (n - export))
	}
	else if (lexer->input[n] == '"')
	{
		n++;
		export++;
		while (lexer->input[n] != '"')
		{
			if (lexer->input[n] == '$')
				n = dollar_solver(lexer->input, n);
			n++;
		}
		//INSERT DESTINATION FOR OUTPUT ft_substr(lexer->input, export, (n - export))
	}
}

int create_new_token(t_lexer *lexer, int type, int n)
{
	
}

int redirect_token_define(t_lexer *lexer, int n)
{
	int type;
	
	type = 0;
	if (lexer->input[n] == '<' && lexer->input[n + 1] == '<')
	{
		type = DOUBLE_IN;
		n++;
	}
	else if (lexer->input[n] == '<' && lexer->input[n + 1] != '<')
		type = SINGLE_IN;
	else if (lexer->input[n] == '>' && lexer->input[n + 1] == '>')
	{
		type = DOUBLE_OUT;
		n++;
	}
	else if (lexer->input[n] == '>' && lexer->input[n + 1] != '>')
		type = SINGLE_OUT;
	return (type);
}

int dollar_solver(char *str, int n)
{
	
}

