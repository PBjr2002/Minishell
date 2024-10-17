/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 20:17:35 by pauberna         ###   ########.fr       */
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

	Hellshell> < <
Syntax error
Hellshell> 
exit
==11247== 
==11247== FILE DESCRIPTORS: 3 open (3 std) at exit.
==11247== 
==11247== HEAP SUMMARY:
==11247==     in use at exit: 232,947 bytes in 240 blocks
==11247==   total heap usage: 602 allocs, 362 frees, 262,591 bytes allocated
==11247== 
==11247== 64 bytes in 1 blocks are definitely lost in loss record 22 of 78
==11247==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==11247==    by 0x11195C: ft_branch_new (tree_and_list_init.c:44)
==11247==    by 0x1122C4: ft_scan_for_redirects1 (tree_creation_utils2.c:30)
==11247==    by 0x11222E: ft_construct_pipelines_zero (tree_creation_utils.c:130)
==11247==    by 0x111F56: tree_creation_function (tree_creation_utils.c:30)
==11247==    by 0x113AC9: parsing (parsing.c:75)
==11247==    by 0x109705: parser_and_exec (prompt.c:52)
==11247==    by 0x1096AB: prompt (prompt.c:39)
==11247==    by 0x1095BA: main (main.c:38)


	------------------------------------------------------------------

	//ls | grep s >>out | wc <out | cat
	TEST THIS COMMAND FOR LEAKS
*/