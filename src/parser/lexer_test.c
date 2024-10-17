/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:10:52 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 18:11:11 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:

REMEMBER THIS ORDER:

    1. Reads command x (done)
    2. Tokenization
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

< infile ls >output | wc < d

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
//\x1b[38;5;91;1mGofastlose input tester> \x1b[0m
//this function will read the input and store it in the lexer->input node, 
//while also checking for open quotes (of both kinds).

void	store_input(t_lexer *lexer)
{
	int		n;
	bool	open_single_quote;
	bool	open_double_quote;

	n = 0;
	open_single_quote = false;
	open_double_quote = false;
	rl_on_new_line();
	lexer->input = readline("Hellshell> ");
	while (lexer->input && lexer->input[n])
	{
		store_input_quote_assist(lexer, &open_single_quote, \
			&open_double_quote, &n);
		n++;
	}
	if ((open_double_quote == true || open_single_quote == true)
		|| !lexer->input || lexer->input[0] == '\0')
		lexer->invalid_lexer = true;
}

void	store_input_quote_assist(t_lexer *lexer, bool *o_s_q,
		bool *o_d_q, int *n)
{
	if (lexer->input[*n] == 39)
	{
		if (*o_s_q == true && *o_d_q == false)
			*o_s_q = false;
		else if (*o_d_q == false)
			*o_s_q = true;
	}
	else if (lexer->input[*n] == 34)
	{
		if (*o_d_q == true && *o_s_q == false)
			*o_d_q = false;
		else if (*o_s_q == false)
			*o_d_q = true;
	}
}

int	input_checker(t_lexer *lexer)
{
	int	n;

	n = 0;
	while (lexer->input[n])
	{
		if (lexer->input[n] > 32 && lexer->input[n] < 127)
			return (1);
		n++;
	}
	return (0);
}

char	**ft_get_env(char **genv)
{
	static char	**env;

	if (genv)
		env = genv;
	return (env);
}
