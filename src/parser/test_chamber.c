/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/10 13:46:11 by lmiguel-         ###   ########.fr       */
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

	an input of <> will segfault... for some reason
	(done)
	
	------------------------------------------------------------------

	duplo heredoc esta a dar um erro

	cat <<out1 | cat <<out2
	>123
	>out1
	>321
	>out2
	
	nosso = There was an error duplicating the FD
	bash = 321
	

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