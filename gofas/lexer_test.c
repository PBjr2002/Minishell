/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:10:52 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/06/17 17:18:34 by lmiguel-         ###   ########.fr       */
/*   Updated: 2024/06/17 17:30:38 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Parsing Rules:
REMEMBER THIS ORDER:
    1. Reads command x
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
void	store_input(void)
{
	t_lexer		*lexer;

	while (1)
	lexer->argc = 0;
	lexer->input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m");
	lexer->argv = ft_split(lexer->input, ' ');
	free(lexer->input);
	if (lexer->argv && lexer->argv[0])
	{
		while (lexer->argv[lexer->argc])
			lexer->argc++;
		lexer->argc = 0;
		lexer->input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m");
		lexer->argv = ft_split(lexer->input, ' ');
		free(lexer->input);
		if (lexer->argv && lexer->argv[0])
		while (lexer->argv[lexer->argc])
		{
			while (lexer->argv[lexer->argc])
				lexer->argc++;
			lexer->argc = 0;
			while (lexer->argv[lexer->argc])
			{
				free(lexer->argv[lexer->argc]);
				lexer->argc++;
			}
			free(lexer->argv);
			free(lexer->argv[lexer->argc]);
			lexer->argc++;
		}
		free(lexer->argv);
	}
}

