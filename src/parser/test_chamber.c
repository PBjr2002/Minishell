/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/16 17:08:24 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"


// this file will contain a compilation of errors which require fixing, please include the result and bash result in the examples, like this:
//
// $?
// NOSSO = 0
// BASH = 0
// clear && make re -s && valgrind --suppressions=sup_readline.supp --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell
// clear && make re -s && ./minishell 

/*
	------------------------------------------------------------------

	expansao de argumentos precisa de ignorar espacos
	
	export A="    ls              -la"
	cat $A

	nosso : cat: '    ls              -la': No such file or directory
	bash : cat: 'ls -la': No such file or directory

	n acho que seja problema porque é uma mensagem de erro e o resto do comportamento do comando está igual

	------------------------------------------------------------------
	
	se mandarmos o input ./././././././. ou /////////////// para o minishell,
	este apresenta um erro "Permission denied"

	./././././././././
	
	nosso = Permission denied
	bash = ./././././././././ : is a directory.

	(n entendi o problema, a mensagem de erro está lá)
	
	(VER MAIS TARDE, MSG DE ERRO INTERESSA?)

	------------------------------------------------------------------

	//ls | grep s >>out | wc <out | cat
	TEST THIS COMMAND FOR LEAKS

--------------------------------------------------------------------------------

Hellshell> $?
==25982== Invalid read of size 8
==25982==    at 0x10F83A: post_command_expand_check (expander_utils.c:149)
==25982==    by 0x1125EC: command_expand (parsing_utils.c:59)
==25982==    by 0x1130C1: parsing (parsing.c:56)
==25982==    by 0x1096EB: parser_and_exec (prompt.c:50)
==25982==    by 0x109691: prompt (prompt.c:37)
==25982==    by 0x1095BA: main (main.c:38)
==25982==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==25982== 
==25982== 
==25982== Process terminating with default action of signal 11 (SIGSEGV)
==25982==  Access not within mapped region at address 0x0
==25982==    at 0x10F83A: post_command_expand_check (expander_utils.c:149)
==25982==    by 0x1125EC: command_expand (parsing_utils.c:59)
==25982==    by 0x1130C1: parsing (parsing.c:56)
==25982==    by 0x1096EB: parser_and_exec (prompt.c:50)
==25982==    by 0x109691: prompt (prompt.c:37)
==25982==    by 0x1095BA: main (main.c:38)
==25982==  If you believe this happened as a result of a stack
==25982==  overflow in your program's main thread (unlikely but
==25982==  possible), you can try to increase the size of the
==25982==  main thread stack using the --main-stacksize= flag.
==25982==  The main thread stack size used in this run was 8388608.

--------------------------------------------------------------------------------

	echo $SHLVL"

	falta o syntax error para poder dar o status=2

-------------------------------------------------------------------------------

	ls > |

	nosso : faz o comando e cria o ficheiro '|'
	bash  : cria o ficheiro '|' mas dá syntax error

-------------------------------------------------------------------------------
*/