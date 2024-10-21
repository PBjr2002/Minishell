/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/21 18:56:15 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// this file will contain a compilation of errors which require fixing, 
// please include the result and bash result in the examples, like this:
//
// $?
// NOSSO = 0
// BASH = 0
// clear && make re -s && valgrind --suppressions=sup_readline.supp 
// --trace-children=yes --track-fds=yes --leak-check=full 
// --show-leak-kinds=all ./minishell
// clear && make re -s && ./minishell 

/*
	------------------------------------------------------------------

	expansao de argumentos precisa de ignorar espacos
	
	export A="    ls              -la"
	cat $A

	nosso : cat: '    ls              -la': No such file or directory
	bash : cat: 'ls -la': No such file or directory

	n acho que seja problema porque é uma mensagem de erro e o resto 
	do comportamento do comando está igual

	------------------------------------------------------------------

	algo se passa na ligacao dos pipes

	cat <<EOF >out1
	
	nosso: heredoc recebe inputs e termina quando recebe o limiter, 
	mas abre um prompt que escreve diretamente para o >out

	bash: heredoc recebe inputs e termina quando recebe o limiter,
	escreve os inputs para o out

	------------------------------------------------------------------

	leak de export

	export a=b
	export a

	LEAK PODE SER EVITADO AO NAO SUBSTITUIRMOS UMA ENVIRONMENT VARIABLE
	SE O EXPORT NAO TIVER UM = VALIDO
	para referencia:

	bash: export a=b
	export a

	(a=b nao e substituido por a)

	==736171== 
==736171== FILE DESCRIPTORS: 3 open (3 std) at exit.
==736171== 
==736171== HEAP SUMMARY:
==736171==     in use at exit: 213,543 bytes in 359 blocks
==736171==   total heap usage: 1,875 allocs, 1,516 frees, 308,288 bytes allocated
==736171== 
==736171== 4 bytes in 1 blocks are definitely lost in loss record 2 of 81
==736171==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==736171==    by 0x40E085: ft_strdup (in /home/lmiguel-/Minishell-Shared/minishell)
==736171==    by 0x40206B: add_env_line (builtins_helper.c:127)
==736171==    by 0x405561: export_helper3 (export.c:99)
==736171==    by 0x40539D: export_helper (export.c:55)
==736171==    by 0x40527A: exec_export (export.c:32)
==736171==    by 0x4018B9: decider (builtins.c:25)
==736171==    by 0x404020: real_exec_cmd (builtins_helper8.c:109)
==736171==    by 0x403F66: exec_cmd (builtins_helper8.c:76)
==736171==    by 0x401783: parser_and_exec (prompt.c:52)
==736171==    by 0x4015B8: prompt (prompt.c:27)
==736171==    by 0x401328: main (main.c:26)
==736171== 
==736171== 3,724 bytes in 63 blocks are definitely lost in loss record 56 of 81
==736171==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==736171==    by 0x40E085: ft_strdup (in /home/lmiguel-/Minishell-Shared/minishell)
==736171==    by 0x402025: add_env_line (builtins_helper.c:122)
==736171==    by 0x405561: export_helper3 (export.c:99)
==736171==    by 0x40539D: export_helper (export.c:55)
==736171==    by 0x40527A: exec_export (export.c:32)
==736171==    by 0x4018B9: decider (builtins.c:25)
==736171==    by 0x404020: real_exec_cmd (builtins_helper8.c:109)
==736171==    by 0x403F66: exec_cmd (builtins_helper8.c:76)
==736171==    by 0x401783: parser_and_exec (prompt.c:52)
==736171==    by 0x4015B8: prompt (prompt.c:27)
==736171==    by 0x401328: main (main.c:26)
==736171== 
==736171== LEAK SUMMARY:
==736171==    definitely lost: 3,728 bytes in 64 blocks
==736171==    indirectly lost: 0 bytes in 0 blocks
==736171==      possibly lost: 0 bytes in 0 blocks
==736171==    still reachable: 0 bytes in 0 blocks
==736171==         suppressed: 209,815 bytes in 295 blocks
==736171== 
==736171== For lists of detected and suppressed errors, rerun with: -s
==736171== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 1 from 1)

	------------------------------------------------------------------

	//ls | grep s >>out | wc <out | cat
	TEST THIS COMMAND FOR LEAKS
*/