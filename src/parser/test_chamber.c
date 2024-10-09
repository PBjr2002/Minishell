/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/09 18:03:29 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"


// this file will contain a compilation of errors which require fixing, please include the result and bash result in the examples, like this:
//
// $?
// NOSSO = 0
// BASH = 0
// clear && make re -s && valgrind --suppressions=sup_readline.supp --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

/*
------------------------------------------------------------------


	ao fazer export de variaveis com espacos, estes sao ignorados.
	isto leva a problemas quando a variavel exportada e usada como comando:

	export hey="ls -a"
	$hey

	nosso = ls -a: command not found
	bash = .  ..  .git  inc  makefile  minishell  obj  README.md  src  sup_readline.supp

	Hellshell> export hey="ls -a"
==6735== Use of uninitialised value of size 8
==6735==    at 0x110D16: command_expand (parsing_utils.c:44)
==6735==    by 0x111262: parsing (parsing.c:56)
==6735==    by 0x1096B7: parser_and_exec (prompt.c:50)
==6735==    by 0x10965D: prompt (prompt.c:37)
==6735==    by 0x10958A: main (main.c:37)
==6735== 
==6735== Invalid read of size 1
==6735==    at 0x110D16: command_expand (parsing_utils.c:44)
==6735==    by 0x111262: parsing (parsing.c:56)
==6735==    by 0x1096B7: parser_and_exec (prompt.c:50)
==6735==    by 0x10965D: prompt (prompt.c:37)
==6735==    by 0x10958A: main (main.c:37)
==6735==  Address 0x4b635a6 is 1 bytes after a block of size 5 alloc'd
==6735==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6735==    by 0x111764: ft_substr (in /home/pbjr/Desktop/Minishell/minishell)
==6735==    by 0x10F0F5: com_token_define (token_define_utils.c:115)
==6735==    by 0x110AC8: tokenization (tokenization.c:108)
==6735==    by 0x109685: parser_and_exec (prompt.c:47)
==6735==    by 0x10965D: prompt (prompt.c:37)
==6735==    by 0x10958A: main (main.c:37)
==6735== 
==6735== Invalid read of size 1
==6735==    at 0x110F75: double_quote_token_remover (parsing_utils.c:135)
==6735==    by 0x1112BB: parsing (parsing.c:63)
==6735==    by 0x1096B7: parser_and_exec (prompt.c:50)
==6735==    by 0x10965D: prompt (prompt.c:37)
==6735==    by 0x10958A: main (main.c:37)
==6735==  Address 0x4b638a2 is 0 bytes after a block of size 2 alloc'd
==6735==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6735==    by 0x111764: ft_substr (in /home/pbjr/Desktop/Minishell/minishell)
==6735==    by 0x10F36D: double_quote_token_define (token_define_utils2.c:50)
==6735==    by 0x10EA7D: quote_token_define (token_define_utils.c:24)
==6735==    by 0x110999: tokenization (tokenization.c:98)
==6735==    by 0x109685: parser_and_exec (prompt.c:47)
==6735==    by 0x10965D: prompt (prompt.c:37)
==6735==    by 0x10958A: main (main.c:37)
==6735== 
==6735== Conditional jump or move depends on uninitialised value(s)
==6735==    at 0x110F7A: double_quote_token_remover (parsing_utils.c:135)
==6735==    by 0x1112BB: parsing (parsing.c:63)
==6735==    by 0x1096B7: parser_and_exec (prompt.c:50)
==6735==    by 0x10965D: prompt (prompt.c:37)
==6735==    by 0x10958A: main (main.c:37)
==6735== 
==6735== Conditional jump or move depends on uninitialised value(s)
==6735==    at 0x1096E9: parser_and_exec (prompt.c:53)
==6735==    by 0x10965D: prompt (prompt.c:37)
==6735==    by 0x10958A: main (main.c:37)
==6735== 

	(solucao simples, basta efetuar uma especie de split e incrementar uma vez todos os elementos da lista de tokens, "empurrar uma vez na direcao do fim")
	(FIXED)
	------------------------------------------------------------------
	
	export nao esta a ser feito corretamente
	export hey="ls -l"
	env

	nosso env = hey=
	bash env = hey=ls -l
	
	------------------------------------------------------------------

	
	ao executar um numero elevado de pipes ao mesmo tempo, o programa 
	nao os fecha corretamente

	echo 123 | cat | cat

	pipes abertos excede os 3 STD e apresenta o erro:
	There was an error duplicating the FD
	|
	
	duplo heredoc esta a dar um erro

	cat <<out1 | cat <<out2
	>123
	>out1
	>321
	>out2
	
	nosso = There was an error duplicating the FD
	bash = 321
	
	------------------------------------------------------------------

	ao enviar apenas uma redirecao, o programa nao a executa
	<<here

	nosso = here: no such file or directory
	bash = (abre heredoc)

	Hellshell> <<here
==7818== Invalid read of size 1
==7818==    at 0x10EC21: redirect_token_define (token_define_utils.c:52)
==7818==    by 0x1109E3: tokenization (tokenization.c:100)
==7818==    by 0x109685: parser_and_exec (prompt.c:47)
==7818==    by 0x10965D: prompt (prompt.c:37)
==7818==    by 0x10958A: main (main.c:37)
==7818==  Address 0x4b61fef is 1 bytes before a block of size 7 alloc'd
==7818==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7818==    by 0x48A8BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==7818==    by 0x4886694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==7818==    by 0x4890D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==7818==    by 0x10E89E: store_input (lexer_test.c:95)
==7818==    by 0x1095E3: prompt (prompt.c:25)
==7818==    by 0x10958A: main (main.c:37)
==7818== 
==7818== Use of uninitialised value of size 8
==7818==    at 0x110D16: command_expand (parsing_utils.c:44)
==7818==    by 0x111262: parsing (parsing.c:56)
==7818==    by 0x1096B7: parser_and_exec (prompt.c:50)
==7818==    by 0x10965D: prompt (prompt.c:37)
==7818==    by 0x10958A: main (main.c:37)
==7818== 
==7818== Invalid read of size 1
==7818==    at 0x110D16: command_expand (parsing_utils.c:44)
==7818==    by 0x111262: parsing (parsing.c:56)
==7818==    by 0x1096B7: parser_and_exec (prompt.c:50)
==7818==    by 0x10965D: prompt (prompt.c:37)
==7818==    by 0x10958A: main (main.c:37)
==7818==  Address 0x5b631f0 is not stack'd, malloc'd or (recently) free'd
==7818== 
==7818== 
==7818== Process terminating with default action of signal 11 (SIGSEGV)
==7818==  Access not within mapped region at address 0x5B631F0
==7818==    at 0x110D16: command_expand (parsing_utils.c:44)
==7818==    by 0x111262: parsing (parsing.c:56)
==7818==    by 0x1096B7: parser_and_exec (prompt.c:50)
==7818==    by 0x10965D: prompt (prompt.c:37)
==7818==    by 0x10958A: main (main.c:37)
==7818==  If you believe this happened as a result of a stack
==7818==  overflow in your program's main thread (unlikely but
==7818==  possible), you can try to increase the size of the
==7818==  main thread stack using the --main-stacksize= flag.
==7818==  The main thread stack size used in this run was 8388608.
==7818== 
==7818== HEAP SUMMARY:
==7818==     in use at exit: 222,152 bytes in 373 blocks
==7818==   total heap usage: 562 allocs, 189 frees, 236,473 bytes allocated
==7818== 
==7818== LEAK SUMMARY:
==7818==    definitely lost: 0 bytes in 0 blocks
==7818==    indirectly lost: 0 bytes in 0 blocks
==7818==      possibly lost: 0 bytes in 0 blocks
==7818==    still reachable: 222,152 bytes in 373 blocks
==7818==         suppressed: 0 bytes in 0 blocks
==7818== Rerun with --leak-check=full to see details of leaked memory
==7818== 
==7818== Use --track-origins=yes to see where uninitialised values come from
==7818== For lists of detected and suppressed errors, rerun with: -s
==7818== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)


	>out
	nosso = out: no such file or directory
	bash = (abre ficheiro chamado out)

Hellshell> >out
==8169== Invalid read of size 1
==8169==    at 0x10EC21: redirect_token_define (token_define_utils.c:52)
==8169==    by 0x1109E3: tokenization (tokenization.c:100)
==8169==    by 0x109685: parser_and_exec (prompt.c:47)
==8169==    by 0x10965D: prompt (prompt.c:37)
==8169==    by 0x10958A: main (main.c:37)
==8169==  Address 0x4b61fef is 1 bytes before a block of size 5 alloc'd
==8169==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==8169==    by 0x48A8BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==8169==    by 0x4886694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==8169==    by 0x4890D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==8169==    by 0x10E89E: store_input (lexer_test.c:95)
==8169==    by 0x1095E3: prompt (prompt.c:25)
==8169==    by 0x10958A: main (main.c:37)
==8169== 
==8169== Use of uninitialised value of size 8
==8169==    at 0x110D16: command_expand (parsing_utils.c:44)
==8169==    by 0x111262: parsing (parsing.c:56)
==8169==    by 0x1096B7: parser_and_exec (prompt.c:50)
==8169==    by 0x10965D: prompt (prompt.c:37)
==8169==    by 0x10958A: main (main.c:37)
==8169== 
==8169== Invalid read of size 1
==8169==    at 0x110D16: command_expand (parsing_utils.c:44)
==8169==    by 0x111262: parsing (parsing.c:56)
==8169==    by 0x1096B7: parser_and_exec (prompt.c:50)
==8169==    by 0x10965D: prompt (prompt.c:37)
==8169==    by 0x10958A: main (main.c:37)
==8169==  Address 0x5b631f0 is not stack'd, malloc'd or (recently) free'd
==8169== 
==8169== 
==8169== Process terminating with default action of signal 11 (SIGSEGV)
==8169==  Access not within mapped region at address 0x5B631F0
==8169==    at 0x110D16: command_expand (parsing_utils.c:44)
==8169==    by 0x111262: parsing (parsing.c:56)
==8169==    by 0x1096B7: parser_and_exec (prompt.c:50)
==8169==    by 0x10965D: prompt (prompt.c:37)
==8169==    by 0x10958A: main (main.c:37)
==8169==  If you believe this happened as a result of a stack
==8169==  overflow in your program's main thread (unlikely but
==8169==  possible), you can try to increase the size of the
==8169==  main thread stack using the --main-stacksize= flag.
==8169==  The main thread stack size used in this run was 8388608.
==8169== 
==8169== HEAP SUMMARY:
==8169==     in use at exit: 222,148 bytes in 373 blocks
==8169==   total heap usage: 562 allocs, 189 frees, 236,467 bytes allocated
==8169== 
==8169== LEAK SUMMARY:
==8169==    definitely lost: 0 bytes in 0 blocks
==8169==    indirectly lost: 0 bytes in 0 blocks
==8169==      possibly lost: 0 bytes in 0 blocks
==8169==    still reachable: 222,148 bytes in 373 blocks
==8169==         suppressed: 0 bytes in 0 blocks
==8169== Rerun with --leak-check=full to see details of leaked memory
==8169== 
==8169== Use --track-origins=yes to see where uninitialised values come from
==8169== For lists of detected and suppressed errors, rerun with: -s
==8169== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)

	------------------------------------------------------------------

	ao enviar varias redirecoes num so comando, apenas a primeira e aberta
	ls >1>2

	nosso = apenas o "1" e aberto, e contem a informacao
	bash = abre o 1 e o 2, com a informacao presente apenas no 2

	agr já cria o 1 e o 2 mas na tree fica assim:
	(gdb) p tree->str
$1 = 0x55555559c1d0 "ls"
(gdb) p tree->left->str
$2 = 0x55555557f1f0 "1"
(gdb) p tree->left->left->str
$3 = 0x55555557f190 "2"
	
	ou seja, o 2 deveria ser o que ficava mais acima porque é o ultimo

	------------------------------------------------------------------

	se mandarmos o input ./././././././. ou /////////////// para o minishell,
	este apresenta um erro "Permission denied"

	./././././././././
	
	nosso = Permission denied
	bash = ./././././././././ : is a directory.

	(n entendi o problema, a mensagem de erro está lá)
	
	
	------------------------------------------------------------------

	se apos efetuarmos um comando invalido efetuarmos um comando valido,
	o shell retorna um syntax error

	ls nonexistentdirectory
	
	ls

	nosso : syntax error
	bash : (executa o ls normalmente)

	------------------------------------------------------------------

	ls nao da append a branches corretamente

	ls 'hey'"hey"

	nosso : ls: cannot access 'hey': No such file or directory
			ls: cannot access 'hey': No such file or directory

	bash : ls: cannot access 'heyhey': No such file or directory


	------------------------------------------------------------------
*/