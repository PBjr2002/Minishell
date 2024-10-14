/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/14 14:39:57 by pauberna         ###   ########.fr       */
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

	ls nao da append a branches corretamente

	ls 'hey'"hey"

	nosso : ls: cannot access 'hey': No such file or directory
			ls: cannot access 'hey': No such file or directory

	bash : ls: cannot access 'heyhey': No such file or directory
	(done)

	------------------------------------------------------------------

	//ls | grep s >>out | wc <out | cat
	TEST THIS COMMAND FOR LEAKS

	----------------------------------------------

	export a=hello b world
	echo $a $b

	nosso:helloworld
	bash :hello world

	hello e world estão com o append before a true quando chegam ao exec_echo
	daí n haver espaço entre as palavras
	
	-------------------------------------------------------------------

	echo "smth"'$PATH'

	'$PATH' está a chegar com a flag do expand como true
	
	(solved, hopefully doesnt break anything)

	-------------------------------------------------------------------

	echo $LOL hi

	nosso : hi
	bash  :hi

	(o problema esta na expansao, so e suposto enviar um espaco quando esta esta
	entre aspas)

	-------------------------------------------------------------------

	echo $"LOL"

	nosso :$LOL
	bash  :LOL

	(apos verificar no gdb, a tree esta a receber isto:)
	echo $"gofas"

			echo
				|
					$
					|
						gofas

	vai ser necessario fazer a expansao deste dollar, porque e do type 5 (TYPE_DOLLAR)
	isto deveria dar uma expansao nula, que por si faria com que o resultado fosse ignorado,
	ficando apenas o echo e o gofas, dando o resultado:

	gofas

	como queremos.
	
	----------------------------------------------------------------

	ls"-l"|wc|grep|echo>>txt.txt<<EOF'A'"|">OUT

	nem eu percebi o que era suposto acontecer aqui

	---------------------------------------------------------------

	echo hi >">" lol

	Hellshell> echo hi >">" lol
==10411== Invalid write of size 8
==10411==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==10411==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==10411==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==10411==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==10411==    by 0x112A93: parsing (parsing.c:73)
==10411==    by 0x1096DC: parser_and_exec (prompt.c:50)
==10411==    by 0x109682: prompt (prompt.c:37)
==10411==    by 0x1095AF: main (main.c:37)
==10411==  Address 0x38 is not stack'd, malloc'd or (recently) free'd
==10411== 
==10411== 
==10411== Process terminating with default action of signal 11 (SIGSEGV)
==10411==  Access not within mapped region at address 0x38
==10411==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==10411==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==10411==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==10411==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==10411==    by 0x112A93: parsing (parsing.c:73)
==10411==    by 0x1096DC: parser_and_exec (prompt.c:50)
==10411==    by 0x109682: prompt (prompt.c:37)
==10411==    by 0x1095AF: main (main.c:37)
==10411==  If you believe this happened as a result of a stack
==10411==  overflow in your program's main thread (unlikely but
==10411==  possible), you can try to increase the size of the
==10411==  main thread stack using the --main-stacksize= flag.
==10411==  The main thread stack size used in this run was 8388608.

	(solved)
-------------------------------------------------------------------------------

	echo HI > > out

	Hellshell> echo HI > > out
==11098== Invalid write of size 8
==11098==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==11098==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==11098==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==11098==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==11098==    by 0x112A93: parsing (parsing.c:73)
==11098==    by 0x1096DC: parser_and_exec (prompt.c:50)
==11098==    by 0x109682: prompt (prompt.c:37)
==11098==    by 0x1095AF: main (main.c:37)
==11098==  Address 0x38 is not stack'd, malloc'd or (recently) free'd
==11098== 
==11098== 
==11098== Process terminating with default action of signal 11 (SIGSEGV)
==11098==  Access not within mapped region at address 0x38
==11098==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==11098==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==11098==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==11098==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==11098==    by 0x112A93: parsing (parsing.c:73)
==11098==    by 0x1096DC: parser_and_exec (prompt.c:50)
==11098==    by 0x109682: prompt (prompt.c:37)
==11098==    by 0x1095AF: main (main.c:37)
==11098==  If you believe this happened as a result of a stack
==11098==  overflow in your program's main thread (unlikely but
==11098==  possible), you can try to increase the size of the
==11098==  main thread stack using the --main-stacksize= flag.
==11098==  The main thread stack size used in this run was 8388608.

-----------------------------------------------------------------------------

	< inc/minishell.h cat

	nosso : n faz nada
	bash  : printa o minishell.h

---------------------------------------------------------------------------

	ls > 1 > 2

	Hellshell> ls > 1 > 2
==11895== Invalid write of size 8
==11895==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==11895==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==11895==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==11895==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==11895==    by 0x112A93: parsing (parsing.c:73)
==11895==    by 0x1096DC: parser_and_exec (prompt.c:50)
==11895==    by 0x109682: prompt (prompt.c:37)
==11895==    by 0x1095AF: main (main.c:37)
==11895==  Address 0x38 is not stack'd, malloc'd or (recently) free'd
==11895== 
==11895== 
==11895== Process terminating with default action of signal 11 (SIGSEGV)
==11895==  Access not within mapped region at address 0x38
==11895==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==11895==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==11895==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==11895==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==11895==    by 0x112A93: parsing (parsing.c:73)
==11895==    by 0x1096DC: parser_and_exec (prompt.c:50)
==11895==    by 0x109682: prompt (prompt.c:37)
==11895==    by 0x1095AF: main (main.c:37)
==11895==  If you believe this happened as a result of a stack
==11895==  overflow in your program's main thread (unlikely but
==11895==  possible), you can try to increase the size of the
==11895==  main thread stack using the --main-stacksize= flag.
==11895==  The main thread stack size used in this run was 8388608.

----------------------------------------------------------------------

	cat | cat | cat | ls

	deveria esperar por input nos 3 cats
	idk why isnt working

--------------------------------------------------------------------------

	echo hi > "|" > lol42
	
Hellshell> echo hi > "|" > lol42
==14194== Invalid write of size 8
==14194==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==14194==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==14194==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==14194==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==14194==    by 0x112A93: parsing (parsing.c:73)
==14194==    by 0x1096DC: parser_and_exec (prompt.c:50)
==14194==    by 0x109682: prompt (prompt.c:37)
==14194==    by 0x1095AF: main (main.c:37)
==14194==  Address 0x38 is not stack'd, malloc'd or (recently) free'd
==14194== 
==14194== 
==14194== Process terminating with default action of signal 11 (SIGSEGV)
==14194==  Access not within mapped region at address 0x38
==14194==    at 0x11067E: ft_redirect_branch_attach1 (tree_and_list_append.c:34)
==14194==    by 0x11190D: ft_scan_for_redirects1 (tree_creation_utils2.c:29)
==14194==    by 0x11144B: ft_construct_pipelines_zero (tree_creation_utils.c:154)
==14194==    by 0x1111B3: tree_creation_function (tree_creation_utils.c:32)
==14194==    by 0x112A93: parsing (parsing.c:73)
==14194==    by 0x1096DC: parser_and_exec (prompt.c:50)
==14194==    by 0x109682: prompt (prompt.c:37)
==14194==    by 0x1095AF: main (main.c:37)
==14194==  If you believe this happened as a result of a stack
==14194==  overflow in your program's main thread (unlikely but
==14194==  possible), you can try to increase the size of the
==14194==  main thread stack using the --main-stacksize= flag.
==14194==  The main thread stack size used in this run was 8388608.

---------------------------------------------------------------------------------------

	export AA=asd AAA=asd = AAAAAA 123=123 AA123_123=@@@ AA@@=asd=asd

	idk why AA@@=asd=asd está a ser visto como valido quando n o devia, maybe verificaçoes de caracteres
	(done)

-----------------------------------------------------------------------------------

	export asd@@@

	again verificaçoes de caracteres, n deveria estar a ser criado mas está
	(done)

-------------------------------------------------------------------------------

	<< LIM cat

	nosso : n sai do heredoc sem ctrl-c
	bash  : sai do heredoc assim que se escreve LIM

--------------------------------------------------------------------------
	testar a partir da linha 79 até a linha 85 o problema é o mesmo
	estão a ser criados 2 redirects em vez de só um então o problema n é o heredoc mas sim o estar a ser feito 2x

------------------------------------------------------------------------------

	echo hi"" "" "" ""there

	nosso :hithere
	bash  :hi   there
*/