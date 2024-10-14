/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/14 16:55:03 by lmiguel-         ###   ########.fr       */
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

	----------------------------------------------------------------

	ls"-l"|wc|grep|echo>>txt.txt<<EOF'A'"|">OUT

	nem eu percebi o que era suposto acontecer aqui

	supostamente, seria para testar o delimiter do heredoc...? n sei qual sera porque o nosso
	nao manda msg de erro a indicar o delimiter quando mandamos ctrl + d

	(o delimiter seria EOFA|)

	testar a partir da linha 79 até a linha 85 o problema é o mesmo
	estão a ser criados 2 redirects em vez de só um então o problema n é o heredoc mas sim o estar a ser feito 2x

----------------------------------------------------------------------

	cat | cat | cat | ls

	deveria esperar por input nos 3 cats
	idk why isnt working

	(esquisito... ele espera por input, mas disfarcado de Hellshell>)
	
------------------------------------------------------------------------------

*/