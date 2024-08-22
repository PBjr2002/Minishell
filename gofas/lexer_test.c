/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:10:52 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/22 17:36:07 by lmiguel-         ###   ########.fr       */
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

#include "minishell.h"

//this function will read the input and store it in the lexer->input node, while also checking for open quotes (of both kinds).
void	store_input(t_lexer *lexer)
{
	int n;
	bool open_single_quote;
	bool open_double_quote;
	
	n = 0;
	open_single_quote = false;
	open_double_quote = false;
	lexer->input = readline("\x1b[38;5;91;1mGofastlose input tester> \x1b[0m");
	while(lexer->input[n])
	{
		if (lexer->input[n] == 39)
		{
			if (open_single_quote == true)
				open_single_quote = false;
			else
				open_single_quote = true;
		}
		else if (lexer->input[n] == 34)
		{
			if (open_double_quote == true)
				open_double_quote = false;
			else
				open_double_quote = true;
		}
		n++;
	}
	if (open_double_quote == true || open_single_quote == true)
		lexer->invalid_lexer = true;
}


//This function searches the whole tree for a type that corresponds to the type given to it by type_to_search (obvious downsizing necessary)
void ft_branch_search(t_tree *actual, int type_to_search)
{
	while (actual->left != NULL)
		{
			actual = actual->left;
			ft_printf("Left branch detected, moving left.\n");
		}
	while (actual->index != 0)
	{
		if (actual->type == type_to_search && actual->solved == false)
			ft_printf("Index: %d, Content: %s, Left Side\n", actual->index, actual->str);
		actual->solved = true;
		ft_printf("Marking as solved.\n");
		if (actual->right != NULL && actual->right->solved == false)
			{
				actual = actual->right;
				ft_printf("Right branch detected, moving right.\n");
			}
		else
			{
				actual = actual->parent;
				ft_printf("Returning to parent.\n");
			}
	}
	if (actual->right != NULL)
		{
			actual = actual->right;
			ft_printf("Right branch detected, moving right.\n");
		}
	while (actual->left != NULL)
		{
			actual = actual->left;
			ft_printf("Left branch detected, moving left.\n");
		}
	while (actual->index != 0)
	{
		if (actual->type == type_to_search && actual->solved == false)
			ft_printf("Index: %d, Content: %s, Right Side\n", actual->index, actual->str);
		actual->solved = true;
		ft_printf("Marking as solved.\n");
		if (actual->right != NULL && actual->right->solved == false)
			{
				actual = actual->right;
				ft_printf("Right branch detected, moving right.\n");
			}
		else
			{
				actual = actual->parent;
				ft_printf("Returning to parent.\n");
			}
	}
	if (actual->index == 0 && actual->type == type_to_search)
			ft_printf("Index: %d, Content: %s, Top of the tree\n", actual->index, actual->str);
}

////////////////////////////////////////////////////////////////////////////TESTING GROUNDS/////////////////////////////////////////////////////////////////////////////////////
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CREATE A NEW MAIN FOR EVERYTHING YOU TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

//this is a simple test of the input storing and quotes checker, as well as solving anything inside single or double quotes (ensure the quotes are the first slot in your input)

/* int main(void)
{
	t_lexer lexer;
	
	while (1)
	{
		lexer.invalid_lexer = false;
		store_input(&lexer);
		//command_id(&lexer);
		if (lexer.invalid_lexer == false)
			continue;
		else
		{
			add_history(lexer.input);
			ft_printf("This is the input: %s\n", lexer.input);
		}
		bracket_solver(&lexer, 0);
	}
	return (0);
} */

//this is used to test the creation, appending and scanning of our tree for all branches containing the type specified in ft_branch_search (starting point seems to not matter.)
//(it does matter, function will not work correctly unless starting point is on the left side of the tree, however can be fixed by traversing the parents up to index 0.)


int main (void)
{
	char *str1 = "cat";
	char *str2 = "|";
	char *str3 = "cat";
	char *str4 = "<< eof";
	char *str5 = "|";
	char *str6 = "cat";
	char *str7 = "|";
	char *str8 = "ls";
	char *str9 = "-l";
	char *str10 = "-l";

	t_tree *pipe0 = ft_branch_new(str7, 0, 6);
	t_tree *pipe1 = ft_branch_new(str5, 2, 6);
	t_tree *pipe2 = ft_branch_new(str2, 4, 6);
	t_tree *cat1 = ft_branch_new(str6, 1, 8);
	t_tree *cat2 = ft_branch_new(str3, 3, 8);
	t_tree *cat3 = ft_branch_new(str1, 5, 8);
	t_tree *ls1 = ft_branch_new(str8, 1, 8);
	t_tree *l1 = ft_branch_new(str9, 2, 7);
	t_tree *l2 = ft_branch_new(str10, 2, 7);
	t_tree *eof = ft_branch_new(str4, 3, 3);
	
	ft_branch_attach(pipe0, cat1, 1);
	ft_branch_attach(pipe0, ls1, 2);
	ft_branch_attach(cat1, pipe1, 1);
	ft_branch_attach(ls1, l1, 2);
	ft_branch_attach(pipe1, eof, 1);
	ft_branch_attach(pipe1, cat2, 2);
	ft_branch_attach(cat2, l2, 2);
	ft_branch_attach(eof, pipe2, 1);
	ft_branch_attach(pipe2, cat3, 1);
	ft_branch_search(pipe0, 6);
}

//cat Makefile | <<eof cat -l | echo 1 2 3 4 5 | ls -l