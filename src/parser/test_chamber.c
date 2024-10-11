/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/11 12:47:01 by pauberna         ###   ########.fr       */
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

	------------------------------------------------------------------
	
	o error code depois de fazermos ctrl + c esta incorreto

	^c
	echo $?

	nosso : 0
	bash : 130
	
	------------------------------------------------------------------
	
	se mandarmos o input ./././././././. ou /////////////// para o minishell,
	este apresenta um erro "Permission denied"

	./././././././././
	
	nosso = Permission denied
	bash = ./././././././././ : is a directory.

	(n entendi o problema, a mensagem de erro está lá)
	
	(VER MAIS TARDE, MSG DE ERRO INTERESSA?)
	
	------------------------------------------------------------------

	se apos efetuarmos um comando invalido efetuarmos um comando valido,
	o shell retorna um syntax error

	ls nonexistentdirectory
	
	ls

	nosso : syntax error
	bash : (executa o ls normalmente)
	(done)

	------------------------------------------------------------------

	ls nao da append a branches corretamente

	ls 'hey'"hey"

	nosso : ls: cannot access 'hey': No such file or directory
			ls: cannot access 'hey': No such file or directory

	bash : ls: cannot access 'heyhey': No such file or directory

	------------------------------------------------------------------

	//ls | grep s >>out | wc <out | cat
	TEST THIS COMMAND FOR LEAKS

	----------------------------------------------

	cd segfault quando se elimina o pwd do export e se muda de diretorio

	--------------------------------------------------

	rever flag do echo:
	-varias flags iguais(juntas ou separadas)
	-espaço depois de uma flag invalida
	(done)

	--------------------------------------------

	export a=b
	export a
	o "a" aparece no env quando deveria n existir
	(done)


*/