/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:10:52 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/06/12 16:43:11 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:

REMEMBER THIS ORDER:


    1. Reads command
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

void	arg_reader(char **argv)
{
	int 	n;
	t_lexer	lexer;
	
	n = 0;
	while (argv && argv[n])
	{
		while (argv[n])
		{
			lexer.str = argv[n];
			lexer.index = n;
			lexer = lexer.next;
			n++;
		}
	}
} 

void	arg_handler(t_simple_cmds simple_cmds, char** argv)
{
	int		n;

	n = 0;
	while (argv && (argv[n] != 32 && (argv[n] < 9 || argv > 13) && argv[n]))
	{
		if (argv[n] == '"')
			n = double_quote_handler(simple_cmds, argv, n);
		else if (argv[n] == 39) // couldn't use ''', so went with ASCII instead
			n = single_quote_handler(simple_cmds, argv, n);
		else
			n = no_quote_handler(simple_cmds, argv, n);
	}
}

void space_handler(t_lexer lexer, char *argv, int n)
{
	//add a space to the token list, with the correct index.
}

int	double_quote_handler(t_lexer lexer, char *argv, int n)
{
	/* 
	ignore everything that is not a $, store everything after the $ until you hit a space, ? or special character,
	compare it to known env variables.
	if it matches, send the variable, otherwise, send nothing.
	examples:
	echo $USER 	-> lmiguel-
	echo $?USER -> 0USER
	echo "$USER" 
	*/
}

int simple_quote_handler(t_lexer lexer, char *argv, int n)
{
	/*
	supposedly, we can ignore everything... until we hit another ' 
	im sure something will show up to become an exception to the rule, like always.
	 */
}

int no_quote_handler(t_lexer lexer, char *argv, int n)
{
	/* 
	everything runs as normal, no ignorance.
	
	 */
}

